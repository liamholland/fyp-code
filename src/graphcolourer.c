#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphcolourer.h"
#include "graphutil.h"

#define AGENT_BREAK_LIMIT 10
#define COLOUR_INCREASE_LIMIT 2

node** agentColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, 
    int (*agentController)(node**, int, int), int (*dynamicKernel)(node***, int*, node*, node***, int*), int save)
{
    node** colouringGraph = copyGraph(graph, numNodes);

    int* problemsAtIteration = (int*)malloc(sizeof(int) * maxIterations);

    int numNoChanges = 0;      //if no agent makes a change in x iterations, the algorithm ends

    //pick some starting nodes for the agents
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

        if(dynamicKernel != NULL) {
            for(int a = 0; a < numAgents; a++) {
                dynamicKernel(&colouringGraph, &numNodes, agents[a], &agents, &numAgents);
            }
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
    free(agents);

    return colouringGraph;
}
