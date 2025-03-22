#include "graphutil.h"
#include "graphgenerator.h"

#include "testUtil.h"

int testInitialiseGraphNoNeighbours() {
    int NUM_NODES = 10;
    
    node** g = initialiseGraph(NUM_NODES, 0);

    for(int n = 0; n < NUM_NODES; n++) {
        if(g[n]->id != n) {
            return 1;
        }

        if(g[n]->degree > 0) {
            return 1;
        }
    }

    return 0;
}

int testInitialiseGraphWithNeighbours() {
    int NUM_NODES = 10;
    int DEGREE = 2;

    node** g = initialiseGraph(NUM_NODES, DEGREE);

    for(int n = 0; n < NUM_NODES; n++) {
        if(g[n]->id != n) {
            return 1;
        }

        if(!(g[n]->degree == DEGREE)) {
            return 1;
        }
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testCopyUnmodifiedGraph() {
    int NUM_NODES = 10;
    
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //copy it
    node** gPrime = copyGraph(g, NUM_NODES);

    //verify
    for(int n = 0; n < NUM_NODES; n++) {
        if(g[n]->id != gPrime[n]->id) {
            return 1;
        }
    }

    freeGraph(g, NUM_NODES);
    freeGraph(gPrime, NUM_NODES);

    return 0;
}

int testCopyModifiedGraph() {
    int NUM_NODES = 10;

    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //pick a node to remove
    int nodeToRemove = (int)(NUM_NODES / 2);

    removeNode(&g, NUM_NODES, g[nodeToRemove]);

    //copy the modified graph
    node** gPrime = copyGraph(g, NUM_NODES - 1);

    //verify
    for(int n = 0; n < NUM_NODES - 1; n++) {
        if(gPrime[n]->id == nodeToRemove) {
            return 1;
        }
    }

    freeGraph(g, NUM_NODES - 1);
    freeGraph(gPrime, NUM_NODES - 1);

    return 0;
}