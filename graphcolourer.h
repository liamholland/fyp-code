#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graphutil.h"

#define AGENT_BREAK_LIMIT 50

node** agentColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves, int (*agentController)(node* agent, int numMoves, int numNodes)) {
    node** colouringGraph = copyGraph(graph, numNodes);

    // int* conflictsAtIterationI = (int*)malloc(sizeof(int) * maxIterations);

    int numNoChangesBreak = 0;      //if no agent makes a change in x iterations, the algorithm ends

    //pick some starting nodes for the "fish"
    node** agents = fetchNUniqueNodes(colouringGraph, numNodes, numAgents);

    //start the iterations
    int i;
    for(i = 0; i < maxIterations; i++) {
        int numChanges = 0;

        //each agent makes changes to the graph
        for(int a = 0; a < numAgents; a++) {
            numChanges += agentController(agents[a], numMoves, numNodes);
        }
        
        // conflictsAtIterationI[i] = findNumConflicts(colouringGraph, numNodes);

        if(!numChanges) {
            numNoChangesBreak++;
            if(numNoChangesBreak == AGENT_BREAK_LIMIT) {
                printf("no changes after %d iterations\n", i);
                break;
            }
        }
        else{
            numNoChangesBreak = 0;
        }
    }

    printf("number of agents: %d; number of colours: %d; number of conflicts: %d; number of missed nodes: %d\n", 
        numAgents, findNumColoursUsed(colouringGraph, numNodes, numNodes), findNumConflicts(colouringGraph, numNodes), findNumUncolouredNodes(colouringGraph, numNodes));

    // write to csv file
    // appendToResults(conflictsAtIterationI, i);

    // free(conflictsAtIterationI);
    // free(agents);

    return colouringGraph;
}

int colourblindFishAgent(node* fish, int numMoves, int numNodes) {
    int numChanges = 0;
    
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
        fish = fish->neighbours[rand() % fish->degree];
    }

    return numChanges;
}

int smartAgent(node* agent, int numMoves, int numNodes) {
    int numChanges = 0;
    
    int* coloursInLocality = findWhichColoursInGraph(agent->neighbours, agent->degree, numNodes);

    coloursInLocality[agent->colour] = 1;

    int max = agent->colour ? agent->colour : numNodes;

    for(int c = 1; c < max; c++) {
        if(!coloursInLocality[c]) {
            agent->colour = c;
            numChanges = 1;
        }
    }

    // free(coloursInLocality); //why does freeing this make the algorithm produce worse results? weird compilation?

    //move the agent
    for(int m = 0; m < numMoves; m++) {
        if(agent->degree == 0) {
            break;  //cant move the agent; on an orphan node
        }
        else if(findNumUncolouredNodes(agent->neighbours, agent->degree) > 0) {
            for(int nb = 0; nb < agent->degree; nb++) {
                if(!agent->neighbours[nb]->colour) {
                    agent = agent->neighbours[nb];
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

            agent = maxColourNode;
        }
    }

    return numChanges;
}

int randomKernel(node* agent, int numMoves, int numNodes) {
    int numChanges = 0;

    if(nodeIsInConflict(agent) || !agent->colour) {
        agent->colour = rand() % numNodes + 1;
        numChanges = 1;
    }

    for(int m = 0; m < numMoves; m++) {
        agent = agent->neighbours[rand() % agent->degree];
    }

    return numChanges;
}