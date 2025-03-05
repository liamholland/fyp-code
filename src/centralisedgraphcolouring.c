#include <stdio.h>
#include "centralisedgraphcolouring.h"
#include "graphutil.h"

// this is really an implementation of the greedy algorithm
// it applies the minimum possible colour to each node once
// not guaranteed to find an optimal solution
// good enough to find a benchmark
node** minimumColour(node** graph, int numNodes) {
    node** colouringGraph = copyGraph(graph, numNodes);

    int m = 1;

    // colour each node
    for(int n = 0; n < numNodes; n++) {

        // find the smallest colour possible to colour it with
        for(int k = 1; k < m + 1; k++) {

            colouringGraph[n]->colour = k;

            if(!nodeIsInConflict(colouringGraph[n])) {
                break;  //break if the node is successfully coloured
            }
            else if(k == m) {
                m++;    //increase m if there is no way to colour it properly
            }
        }
    }

    printf("centralised colour: %d\n", m);

    return colouringGraph;
}