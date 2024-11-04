#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graphutil.h"

// this literally just has each node choose a random colour between 1 and the max colour (== numNodes)
// however, it only changes its colour if it is conflicting with its neighbours
// it continues until there were no conflicts or the cutoff of maxIterations
// the current implementation will not necessarily find the best solution, but the one before the first failure
node** imFeelingLuckyColour(node** graph, int numNodes, int maxIterations) {
    srand((unsigned) time(NULL));

    int maxColour = numNodes;   //the ultimate maximum is a different colour for every node

    node** colouringGraph = copyGraph(graph, numNodes);     //this graph is used to find colouring solutions
    int* lastBestSolution = extractGraphColours(colouringGraph, numNodes);   //array to store colouring solutions. centralised?

    while(maxColour > 0) {
        int anyConflicts = 0;

        //random colour
        for(int i = 0; i < maxIterations; i++) {
            anyConflicts = 0;

            for(int n = 0; n < numNodes; n++) {

                for(int nb = 0; nb < colouringGraph[n]->degree; nb++) {

                    //if the neighbour colour matches the node colour or the node has not been assigned a colour
                    if(colouringGraph[n]->neighbours[nb]->colour == colouringGraph[n]->colour || !colouringGraph[n]->colour) {
                        colouringGraph[n]->colour = rand() % maxColour + 1;
                        anyConflicts = 1;
                        break;
                    }
                }
            }

            //stopping condition for random colour
            if(!anyConflicts) {
                break;
            }
        }

        if(!anyConflicts) {
            free(lastBestSolution);
            lastBestSolution = extractGraphColours(colouringGraph, numNodes);
        }
        else {
            break;
        }
        resetGraphColours(colouringGraph, numNodes);    //reset colouring graph
        maxColour--;
    }

    applyColouring(colouringGraph, lastBestSolution, numNodes);

    free(lastBestSolution);

    printf("final max colour: %d\n", maxColour + 1);    //+1 because the current max was the attempt that did not work
    
    // UNCOMMENT THE BELOW LINE TO VERIFY EVERY COLOUR FROM 1..(maxColour + 1) IS USED IN THE COLOURING
    // printf("chromatic colour: %d\n", findNumColoursUsed(lastBestSolution, numNodes, maxColour + 1)); 

    return colouringGraph;
}

node** noGlobalKnowledgeColour(node** graph, int numNodes, int maxIterations, int numAnts) {
    node** colouringGraph = copyGraph(graph, numNodes);

    int numNoChangeBreak = 10;
    int numNoChangePerculate = 5;

    node** antLocations = fetchNUniqueNodes(colouringGraph, numNodes, numAnts);

    printGraph(antLocations, numAnts);

    return colouringGraph;
}