#include "graphutil.h"
#include "testUtil.h"

int testInitialiseGraphNoNeighbours() {
    int NUM_NODES = 10;
    
    node** g = initialiseGraph(NUM_NODES, 0);

    for(int i = 0; i < NUM_NODES; i++) {
        if(g[i]->id != i) {
            return 1;
        }

        if(g[i]->degree > 0) {
            return 1;
        }
    }

    return 0;
}

int testInitialiseGraphWithNeighbours() {
    int NUM_NODES = 10;
    int DEGREE = 2;

    node** g = initialiseGraph(NUM_NODES, DEGREE);

    for(int i = 0; i < NUM_NODES; i++) {
        if(g[i]->id != i) {
            return 1;
        }

        if(!(g[i]->degree == DEGREE)) {
            return 1;
        }
    }

    return 0;
}