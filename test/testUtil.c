#include <stdlib.h>
#include "graphutil.h"
#include "graphgenerator.h"
#include "testUtil.h"

#define NUM_NODES 10

int testInitialiseGraphNoNeighbours() {
    node** g = initialiseGraph(NUM_NODES, 0);

    for(int n = 0; n < NUM_NODES; n++) {
        if(g[n]->id != n) {
            return 1;
        }

        if(g[n]->degree > 0) {
            return 1;
        }
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testInitialiseGraphWithNeighbours() {
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

int testFreeGraph() {
    //create a graph with neighbours
    node** g = initialiseGraph(NUM_NODES, 1);

    //free it
    freeGraph(g, NUM_NODES);

    //create a graph with no neighbours
    g = initialiseGraph(NUM_NODES, 0);

    //free it
    freeGraph(g, NUM_NODES);

    return 0;   //can basically just test that we make it to this point
}

int testFindNumColoursUsed() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply a colouring
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = g[n]->id + 1;
    }

    //verify
    int numColours = findNumColoursUsed(g, NUM_NODES, NUM_NODES);
    if(numColours != NUM_NODES) {
        return 1;
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testCountNumConflictsAll() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply a colouring
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = 1;
    }

    //verify
    //number of conflicts is n - 1 + n - 2 + ... + 1 == (n * (n - 1)) / 2
    int numConflicts = findNumConflicts(g, NUM_NODES);
    if(numConflicts != (NUM_NODES * (NUM_NODES - 1)) / 2) {
        return 1;
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testCountNumConflictsNone() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //verify
    int numConflicts = findNumConflicts(g, NUM_NODES);
    if(numConflicts > 0) {
        return 1;
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testNumUncolouredNodes() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //verify
    int numUncolouredNodes = findNumUncolouredNodes(g, NUM_NODES);
    if(numUncolouredNodes != NUM_NODES) {
        return 1;
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testFetchNodes() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //select nodes
    node** selectedNodes = fetchNUniqueNodes(g, NUM_NODES, NUM_NODES / 2);
    
    //verify
    for(int n = 0; n < NUM_NODES / 2; n++) {
        //verify the pointer is in g

        int foundNode = 0;

        for(int i = 0; i < NUM_NODES; i++) {
            if(g[i] == selectedNodes[n]) {
                foundNode = 1;
            }
        }

        if(!foundNode) {
            return 1;
        }
    }

    free(selectedNodes);
    freeGraph(g, NUM_NODES);

    return 0;
}

int testFetchNodesMoreThanGraph() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //select nodes
    node** selectedNodes = fetchNUniqueNodes(g, NUM_NODES, NUM_NODES + 1);

    //verify
    for(int n = 0; n < NUM_NODES; n++) {
        //verify the pointer is in g

        int foundNode = 0;

        for(int i = 0; i < NUM_NODES; i++) {
            if(g[i] == selectedNodes[n]) {
                foundNode = 1;
            }
        }

        if(!foundNode) {
            return 1;
        }
    }

    free(selectedNodes);
    freeGraph(g, NUM_NODES);

    return 0;
}

//node in conflict

//find which colours in graph

//find the conflicting nodes in the graph

//find the conflicting neighbours for node

//remove edge

//make node orphan

//remove node

//add edge

//find node with highest degree

//find node with lowest degree

//remove all instances of pointer from list

//find most common colour in graph

//find node with id
