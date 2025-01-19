#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphcolourer.h"
#include "graphutil.h"

#define AGENT_BREAK_LIMIT 10
#define COLOUR_INCREASE_LIMIT 2

node** agentColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, int (*agentController)(node** agent, int numMoves, int numNodes), int save) {
    node** colouringGraph = copyGraph(graph, numNodes);

    int* problemsAtIteration = (int*)malloc(sizeof(int) * maxIterations);

    int numNoChanges = 0;      //if no agent makes a change in x iterations, the algorithm ends

    //pick some starting nodes for the "fish"
    node** agents = fetchNUniqueNodes(colouringGraph, numNodes, numAgents);

    int numColours = minColour;

    //start the iterations
    int i;
    for(i = 0; i < maxIterations; i++) {
        int numChanges = 0;

        //each agent makes changes to the graph
        for(int a = 0; a < numAgents; a++) {
            numChanges += agentController(&agents[a], numMoves, numColours);
        }

        //CONSIDER: this is pretty slow; should i include this every iteration or maybe every nth iteration?
        if(save) {
            problemsAtIteration[i] = findNumConflicts(colouringGraph, numNodes) + findNumUncolouredNodes(colouringGraph, numNodes);
        }

        if(!numChanges) {
            numNoChanges++;
            if(numNoChanges == COLOUR_INCREASE_LIMIT && numColours < maxColour) {
                numColours++;
                numNoChanges = 0;
            }
            else if(numNoChanges >= AGENT_BREAK_LIMIT) {
                printf("ran for %d iterations\n", i);
                break;
            }
        }
        else{
            numNoChanges = 0;
        }
    }

    printf("number of agents: %d; number of colours: %d; number of conflicts: %d; number of missed nodes: %d\n", 
        numAgents, findNumColoursUsed(colouringGraph, numNodes, numNodes), findNumConflicts(colouringGraph, numNodes), findNumUncolouredNodes(colouringGraph, numNodes));

    if(save) {
        // write to csv file
        appendToResults(problemsAtIteration, i);
    }

    free(problemsAtIteration);

    //TODO: update fetchNUnique Nodes
    //this "if" is here because freeing this pointer breaks the code if the pointer is the same as the original graph pointer
    //the pointers are the same if numNodes >= numAgents (see graphutil.h -> fetchNUniqueNodes)
    //need to copy the pointer instead or just embrace the unoptimal solution
    if(numAgents < numNodes) {
        free(agents);
    }

    return colouringGraph;
}

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
        agent->colour = agent->degree;  //something more interesting here maybe?
    }
    else if(nodeIsInConflict(agent)) {
        node** conflicts = findConflictingNeighboursForNode(agent);
        
        removeEdge(agentPointer, conflicts[0]); //remove the first conflict because why not

        numChanges = 1;
    }

    //move the agent
    for(int m = 0; m < numMoves; m++) {
        *agentPointer = agent->neighbours[rand() % agent->degree];
        agent = *agentPointer;
    }

    return numChanges;
}