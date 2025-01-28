#include <stdlib.h>
#include <stdio.h>
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

    if(!agent->colour) {
        agent->colour = max;
        numChanges = 1;
    }

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

// ##### AMONG US KERNEL #####

//functional variables
node* badActor;
int badActorSelected = 0;   //boolean flag(?)

//implementation variables
typedef struct voteStruct {
    node* nodePointer;
    int count;
} vote;

int kernelCallNumber = 0;   //keeps track of the number of times the kernal has been incremented
vote* badActorVotes;
int numVotes = 0;

int amongUsKernel(node** agentPointer, int numMoves, int maxColour) {
    //if the agent is the bad actor, it should pick the least optimal colour
    //if it is a normal node, it should do a normal colouring
    //normal nodes can also vote for the neighbour they believe is the bad actor
    //if the normal nodes manage to identify the bad actor, they can remove it

    kernelCallNumber++;

    int numChanges = 0;

    node* agent = *agentPointer;

    //select the bad actor
    if(!badActorSelected && rand() % 100 == 0) {
        badActor = agent;
        badActorSelected = 1;
    }

    if(agent == badActor && agent->degree > 0) {
        //set the colour to the most common among its neighbours
        int mostCommon = findMostCommonColourInGraph(agent->neighbours, agent->degree, maxColour);
        if(mostCommon != agent->colour) {
            agent->colour = mostCommon;
            numChanges = 1;
        }
    }
    else {
        //vote for the bad actor
        if(nodeIsInConflict(agent)) {
            node** conflictingNodes = findConflictingNeighboursForNode(agent);
            node* nodeVote = conflictingNodes[0];
            free(conflictingNodes);

            int voted = 0;
            for(int i = 0; i < numVotes; i++) {
                if(badActorVotes[i].nodePointer = nodeVote) {
                    badActorVotes[i].count++;
                    voted = 1;
                }
            }

            if(!voted) {
                //create a new pointer to vote for
                struct voteStruct newVote;
                newVote.count = 1;
                newVote.nodePointer = nodeVote;

                badActorVotes = (vote*)realloc(badActorVotes, sizeof(vote) * ++numVotes);
                badActorVotes[numVotes - 1] = newVote;
            }
        }

        //colour the node
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
    }

    //tally vote results
    if(numVotes > 0 && kernelCallNumber >= maxColour) {
        //loop over the array, keeping track of whether a pointer has been seen before with a truth vector
        //when we encounter a new pointer, iterate over the entire array to count how many times it appears
        //or create a vote struct, which has the pointer value and the count
        //then just loop over it twice-ish

        vote* mostVotes = NULL;
        for(int i = 0; i < numVotes; i++) {
            if(mostVotes == NULL || badActorVotes[i].count > mostVotes->count) {
                mostVotes = &badActorVotes[i];
            }
        }

        printf("selected most votes: %d\n", mostVotes->count);

        //make the voted node an orphan
        if(mostVotes->count > 1) {
            makeNodeOrpan(mostVotes->nodePointer);

            if(mostVotes->nodePointer == badActor) {
                printf("the collective identified the imposter\n");
            }
            else{
                printf("incorrect vote made\n");
            }
        }

        //reset
        kernelCallNumber = 0;
        numVotes = 0;
        free(badActorVotes);
        badActorVotes = NULL;
    }

    //move the agent(?)
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
    //vote every maxColour iterations?
    //vote on an array of pointers that represent nodes (remove the ability for agents to move for now)
    //  or maybe only the bad actor can/cannot move

    return numChanges;
}