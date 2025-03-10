#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphcolourer.h"
#include "graphutil.h"
#include "saving.h"

#define AGENT_BREAK_LIMIT 10
#define COLOUR_INCREASE_LIMIT 2

node** agentColour(node** graph, int* numNodesPtr, int maxIterations, int* numAgentsPtr, int numMoves, int minColour, int maxColour, int save,
    int (*colouringKernel)(node*, int),
    int (*dynamicKernel)(node***, int*, node*, node***, int*),
    node* (*movementKernel)(node*, int))
{
    int numNodes = *numNodesPtr;
    int numAgents = *numAgentsPtr;

    node** colouringGraph = copyGraph(graph, numNodes);

    int* problemsAtIteration = (int*)malloc(sizeof(int) * maxIterations);

    int numNoChanges = 0;      //if no agent makes a change in x iterations, the algorithm ends

    //pick some starting nodes for the agents
    node** agents = fetchNUniqueNodes(colouringGraph, numNodes, numAgents);

    int numColours = minColour;

    //start the timer
    clock_t start = clock();

    double ioTime = 0.0;    //time used to account for io operations

    //start the iterations
    int i;
    for(i = 0; i < maxIterations; i++) {
        int numChanges = 0;

        //each agent makes changes to the graph
        for(int a = 0; a < numAgents; a++) {
            numChanges += colouringKernel(agents[a], numColours);

            if(movementKernel != NULL) {
                agents[a] = movementKernel(agents[a], numMoves);
            }
        }

        if(dynamicKernel != NULL) {
            for(int a = 0; a < numAgents; a++) {
                numChanges += dynamicKernel(&colouringGraph, &numNodes, agents[a], &agents, &numAgents);
            }
        }

        if(save) {
            clock_t problemsStart = clock();

            //this is not really "io", but it falls into the "io" category imo
            //either way it takes a really long time
            problemsAtIteration[i] = findNumConflicts(colouringGraph, numNodes) + findNumUncolouredNodes(colouringGraph, numNodes);

            clock_t problemsEnd = clock();
            ioTime += (double)(problemsEnd - problemsStart) / CLOCKS_PER_SEC;
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

    clock_t end = clock();
    double overallTime = (double)(end - start) / CLOCKS_PER_SEC;
    double time = overallTime - ioTime; //subtract the time spent counting conflicts

    int finalNumColours = findNumColoursUsed(colouringGraph, numNodes, numNodes); 
    int numConflicts = findNumConflicts(colouringGraph, numNodes);
    int numMissedNodes = findNumUncolouredNodes(colouringGraph, numNodes);

    printf(
        "number of nodes at start: %d\nnumber of nodes now: %d\nnumber of agents: %d\nnumber of colours: %d\nnumber of conflicts: %d\nnumber of missed nodes: %d\ntime: %.4f seconds\n\n", 
        *numNodesPtr, numNodes, numAgents, finalNumColours, numConflicts, numMissedNodes, time
    );

    if(save) {
        // write to csv file
        appendToResults(problemsAtIteration, i);
        saveColouringData(maxColour, *numNodesPtr, numNodes, i, numAgents, finalNumColours, numConflicts, numMissedNodes, time);
    }

    //update original value of numNodes and numAgents
    *numNodesPtr = numNodes;
    *numAgentsPtr = numAgents;

    free(problemsAtIteration);
    free(agents);

    return colouringGraph;
}

node** pathColour(node** graph, int numNodes, node* firstStartingNode, node* secondStartingNode, int minColour, int maxColour, int save,
    int (*colouringKernel)(node*, int)
) {
    node** colouringGraph = copyGraph(graph, numNodes);

    //find the starting point in the new graph
    node* copyFirstStartingNode = findNodeWithIdInGraph(colouringGraph, numNodes, firstStartingNode->id);
    
    if(copyFirstStartingNode == NULL) {
        printf("failed to find first starting node in graph copy; aborting\n");
        return NULL;
    }
    
    node* copySecondStartingNode = findNodeWithIdInGraph(colouringGraph, numNodes, secondStartingNode->id);

    if(copyFirstStartingNode == NULL) {
        printf("failed to find second starting node in graph copy; aborting\n");
        return NULL;
    }

    //queue structure
    node** colouringQueue = (node**)malloc(sizeof(node*) * (numNodes * numNodes));

    // add both starting nodes manually
    colouringQueue[0] = copyFirstStartingNode;
    colouringQueue[1] = copySecondStartingNode;
    int queueLength = 2;

    //check the next node in the list
    //try to colour it
    //if numChanges > 1, add its neighbours to the queue
    //remove the node from the queue

    int numUpdates = 0;

    while(queueLength > 0) {
        printf("queue length: %d\n", queueLength);

        int numChanges = colouringKernel(colouringQueue[0], maxColour);

        if(numChanges > 0) {
            numUpdates++;

            //add neighbours to queue if they are not already there
            for(int nb = 0; nb < colouringQueue[0]->degree; nb++) {
                for(int q = 0; q < queueLength; q++) {
                    if(colouringQueue[q] == colouringQueue[0]->neighbours[nb]) continue;
                }
                colouringQueue[queueLength++] = colouringQueue[0]->neighbours[nb];
            }
        }

        //shift queue up one
        for(int n = 0; n < queueLength - 1; n++) {
            colouringQueue[n] = colouringQueue[n + 1];
        }

        colouringQueue[--queueLength] = NULL;   //decrement queue length
    }

    //repeat the process until the queue is empty

    free(colouringQueue);

    //print the new data, the number of updated nodes
    printf("number of updates: %d\n\n", numUpdates);

    //return the new coloured graph
    return colouringGraph;
}