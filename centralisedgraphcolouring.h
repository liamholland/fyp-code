#include <stdio.h>
#include "node.h"
#include "graphutil.h"

node** backtrackingColour(node** graph, int numNodes) {
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
                    if(colouringGraph[n - 1]->colour == m) {
                        m++;
                    }

                    //looks like i dont need to backtrack for this implementation for it to work?
                    // n -= 2; // 2 steps back 1 step forward (for loop over n)
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

    printf("chromatic colour: %d\n", chromaticColour);

    return colouringGraph;
}