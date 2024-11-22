#include <stdio.h>
#include "centralisedgraphcolouring.h"
#include "graphutil.h"

// this is really an implementation of the greedy algorithm
// it applies the minimum possible colour to each node once
// not guaranteed to find an optimal solution
// good enough to find a benchmark
node** minimumColour(node** graph, int numNodes) {
    node** colouringGraph = copyGraph(graph, numNodes);

    int chromaticColour = numNodes;

    for(int m = 1; m < numNodes + 1; m++) {

        for(int n = 0; n < numNodes; n++) {

            for(int k = 1; k < m + 1; k++) {

                colouringGraph[n]->colour = k;

                if(!nodeIsInConflict(colouringGraph[n])) {
                    break;
                }
                else if(k == m) {
                    m++;
                }
            }
        }

        if(findNumConflicts(colouringGraph, numNodes) == 0) {
            chromaticColour = m;
            break;
        }
        else {
            resetGraphColours(colouringGraph, numNodes);
        }
    }

    printf("centralised colour: %d\n", chromaticColour);

    return colouringGraph;
}