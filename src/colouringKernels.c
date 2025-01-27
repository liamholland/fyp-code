#include <stdlib.h>
#include "graphutil.h"
#include "colouringKernels.h"

int colourblindFishAgentIncrement(node** fishPointer, int numMoves, int maxColour) {
    int numChanges = 0;
    
    node* fish = *fishPointer;

    //check for conflicts in neighbours
    if(!fish->colour || nodeIsInConflict(fish)) {
        fish->colour = (fish->colour + 1) % (fish->degree + 1);

        if(!fish->colour) {
            fish->colour++;
        }

        numChanges = 1;
    }

    //the fish wanders in its locality
    for(int m = 0; m < numMoves; m++) {
        *fishPointer = fish->neighbours[rand() % fish->degree];
        fish = *fishPointer;
    }

    return numChanges;
}

int colourblindFishAgentDecrement(node** fishPointer, int numMoves, int maxColour) {
    int numChanges = 0;
    
    node* fish = *fishPointer;

    //check for conflicts in neighbours
    if(!fish->colour || nodeIsInConflict(fish)) {
        fish->colour--;

        if(fish->colour <= 0) {
            fish->colour = fish->degree + 1;
        }

        numChanges = 1;
    }

    //the fish wanders in its locality
    for(int m = 0; m < numMoves; m++) {
        *fishPointer = fish->neighbours[rand() % fish->degree];
        fish = *fishPointer;
    }

    return numChanges;
}

int minimumAgent(node** agentPointer, int numMoves, int maxColour) {
    int numChanges = 0;

    node* agent = *agentPointer;

    int* coloursInLocality = findWhichColoursInGraph(agent->neighbours, agent->degree, maxColour);

    coloursInLocality[agent->colour] = 1;

    int max = agent->colour ? agent->colour : maxColour;

    for(int c = 1; c < max; c++) {
        if(!coloursInLocality[c]) {
            agent->colour = c;
            numChanges = 1;
        }
    }

    free(coloursInLocality);

    //move the agent
    for(int m = 0; m < numMoves; m++) {
        if(agent->degree == 0) {
            break;  //cant move the agent; on an orphan node
        }
        else if(findNumUncolouredNodes(agent->neighbours, agent->degree) > 0) {
            for(int nb = 0; nb < agent->degree; nb++) {
                if(!agent->neighbours[nb]->colour) {
                    *agentPointer = agent->neighbours[nb];
                    agent = *agentPointer;
                }
            }
        }
        else {
            node* maxColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour > maxColourNode->colour) {
                    maxColourNode = agent->neighbours[nb];
                }
            }

            *agentPointer = maxColourNode;
            agent = *agentPointer;
        }
    }

    return numChanges;
}

int randomKernel(node** agentPointer, int numMoves, int maxColour) {
    int numChanges = 0;

    node* agent = *agentPointer;

    if(nodeIsInConflict(agent) || !agent->colour) {
        agent->colour = rand() % maxColour + 1;
        numChanges = 1;
    }

    for(int m = 0; m < numMoves; m++) {
        *agentPointer = agent->neighbours[rand() % agent->degree];
        agent = *agentPointer;
    }

    return numChanges;
}

int edgeChopperKernel(node** agentPointer, int numMoves, int maxColour) {
    int numChanges = 0;

    node* agent = *agentPointer;

    if(!agent->colour) {
        agent->colour = maxColour < agent->degree ? maxColour : agent->degree;  //something more interesting here maybe?
    }
    else if(nodeIsInConflict(agent)) {
        node** conflicts = findConflictingNeighboursForNode(agent);

        removeEdge(agent, conflicts[0]); //remove the first conflict because why not

        numChanges = 1;

        free(conflicts);
    }

    //move the agent
    for(int m = 0; m < numMoves; m++) {
        *agentPointer = agent->neighbours[rand() % agent->degree];
        agent = *agentPointer;
    }

    return numChanges;
}

node* badActor;
int badActorSelected = 0;   //boolean flag(?)

int amongUsKernel(node** agentPointer, int numMoves, int maxColour) {
    //if the agent is the bad actor, it should pick the least optimal colour
    //if it is a normal node, it should do a normal colouring
    //normal nodes can also vote for the neighbour they believe is the bad actor
    //if the normal nodes manage to identify the bad actor, they can remove it

    int numChanges = 0;

    node* agent = *agentPointer;

    //select the bad actor
    if(!badActorSelected && rand() % 100 == 0) {
        badActor = agent;
        badActorSelected = 1;
    }

    int* colours = findWhichColoursInGraph(agent->neighbours, agent->degree, maxColour);

    colours[agent->colour] = 1;

    int max = agent->colour ? agent->colour : maxColour;

    //colour the node
    if(agent == badActor) {
        if(agent->colour < maxColour) {
            agent->colour = maxColour;
            numChanges = 1;
        }
    }
    else {
        for(int c = 1; c < max; c++) {
            if(!colours[c]) {
                agent->colour = c;
                numChanges = 1;
            }
        }
    }

    free(colours);

    //move the agent
    for(int m = 0; m < numMoves; m++) {
        if(agent->degree == 0) {
            break;  //cant move the agent; on an orphan node
        }
        else if(findNumUncolouredNodes(agent->neighbours, agent->degree) > 0) {
            for(int nb = 0; nb < agent->degree; nb++) {
                if(!agent->neighbours[nb]->colour) {
                    *agentPointer = agent->neighbours[nb];
                    agent = *agentPointer;

                    if(agent = badActor) {
                        badActor = agent;
                    }

                    break;
                }
            }
        }
        else if(agent == badActor) {
            node* minColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour < minColourNode->colour) {
                    minColourNode = agent->neighbours[nb];
                }
            }

            *agentPointer = minColourNode;
            agent = *agentPointer;
            badActor = agent;
        }
        else {
            node* maxColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour > maxColourNode->colour) {
                    maxColourNode = agent->neighbours[nb];
                }
            }

            *agentPointer = maxColourNode;
            agent = *agentPointer;
        }
    }

    //if the collective is confident in their choice of imposter
    //makeNodeOrphan(badActor)
    //can pair this with a remove orphan dynamic kernel to remove the voted nodes from the graph entirely

    return numChanges;
}