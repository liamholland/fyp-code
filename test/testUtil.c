#include <stdlib.h>
#include <stdio.h>
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

    return 0;
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

int testNodeInConflict() {
    //create two nodes
    node** g = initialiseGraph(2, 1);

    g[0]->neighbours[0] = g[1];
    g[1]->neighbours[0] = g[0];

    if(nodeIsInConflict(g[0]) || nodeIsInConflict(g[1])) {
        return 1;
    }

    g[0]->colour = 1;
    g[1]->colour = 1;

    if(!nodeIsInConflict(g[0]) || !nodeIsInConflict(g[1])) {
        return 1;
    }

    freeGraph(g, 2);

    return 0;
}

int testWhichColoursInGraphOnlyOne() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply colouring
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = 1;
    }

    //get colour truth vector
    int* truthVector = findWhichColoursInGraph(g, NUM_NODES, NUM_NODES);

    //verify
    if(truthVector[1] == 0) return 1;

    for(int i = 0; i < NUM_NODES; i++) {
        if(i != 1 && truthVector[i] > 0) {
            return 1;
        }
    }

    free(truthVector);
    freeGraph(g, NUM_NODES);

    return 0;
}

int testWhichColoursInGraphAll() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply colouring
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = g[n]->id + 1;
    }

    //get truth vector
    int* truthVector = findWhichColoursInGraph(g, NUM_NODES, NUM_NODES + 1);

    //verify
    for(int i = 1; i < NUM_NODES + 1; i++) {
        if(truthVector[i] != 1) {
            return 1;
        }
    }

    free(truthVector);
    freeGraph(g, NUM_NODES);

    return 0;
}

int testFindConflictingNeighbours() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply same colouring to every node
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = 1;
    }

    //verify
    node** conflictingNodes = findConflictingNeighboursForNode(g[0]);
    for(int n = 0; n < NUM_NODES - 1; n++) {
        if(conflictingNodes[n]->id != n + 1) {
            return 1;
        }
    }

    free(conflictingNodes);
    freeGraph(g, NUM_NODES);

    return 0;
}

int testFindConflictingNeighboursNoConflicts() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply colouring to every node
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = g[n]->id + 1;
    }

    //verify
    node** conflictingNodes = findConflictingNeighboursForNode(g[0]);
    if(conflictingNodes != NULL) {
        return 1;
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testCountNumberOfConflictsForNode() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //apply same colour to each node
    for(int n = 0; n < NUM_NODES; n++) {
        g[n]->colour = 1;
    }

    //verify
    int numConflicts = findNumberOfConflictsForNode(g[0]);
    if(numConflicts != NUM_NODES - 1) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}

int testRemoveEdge() {
    //create two nodes
    node** g = initialiseGraph(2, 1);

    g[0]->neighbours[0] = g[1];
    g[1]->neighbours[0] = g[0];

    removeEdge(g[0], g[1]);

    //verify
    if(g[0]->degree > 0) return 1;
    if(g[1]->degree > 0) return 1;

    freeGraph(g, 2);

    return 0;
}

int testMakeNodeOrphan() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //make one an orphan
    makeNodeOrpan(g[0]);

    //verify
    if(g[0]->degree > 0) return 1;
    if(g[0]->neighbours != NULL) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}

int testRemoveNode() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //remove a node
    int idToRemove = g[0]->id;
    removeNode(&g, NUM_NODES, g[0]);

    //verify
    for(int n = 0; n < NUM_NODES - 1; n++) {
        for(int nb = 0; nb < g[n]->degree; nb++) {
            if(g[n]->neighbours[nb]->id == idToRemove) {
                return 1;
            }
        }
    }

    freeGraph(g, NUM_NODES - 1);

    return 0;
}

int testAddEdge() {
    //create graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    makeNodeOrpan(g[0]);

    //add an edge between two nodes
    addEdgeBetweenNodes(g[0], g[1]);

    //verify
    if(g[0]->degree != 1) return 1;
    if(g[0]->neighbours[0] != g[1]) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}

int testFindHighestDegree() {
    //create a graph of orphans
    node** g = generateRandomGraph(NUM_NODES, 0);

    for(int n = 1; n < NUM_NODES; n++) {
        addEdgeBetweenNodes(g[0], g[n]);
    }

    node* highest = findNodeWithHighestDegree(g, NUM_NODES);

    //verify
    if(highest != g[0]) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}

int testFindLowestDegree() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    makeNodeOrpan(g[0]);

    node* lowest = findNodeWithLowestDegree(g, NUM_NODES);

    //verify
    if(lowest != g[0]) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}

int testRemoveNodePointerFromList() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //create a list of nodes
    int listLength = NUM_NODES;
    node** nodePtrs = (node**)malloc(sizeof(node*) * NUM_NODES);

    for(int n = 0; n < NUM_NODES / 2; n++) {
        nodePtrs[n] = g[0];
    }

    for(int n = NUM_NODES / 2; n < NUM_NODES; n++) {
        nodePtrs[n] = g[1];
    }

    //remove g[0] from the list
    removeAllInstancesOfNodePointerFromList(&nodePtrs, g[0], &listLength);
    
    //verify
    if(listLength != NUM_NODES / 2) return 1;
    for(int n = 0; n < listLength; n++) {
        if(nodePtrs[n] == g[0]) {
            return 1;
        }
    }

    freeGraph(g, NUM_NODES);

    return 0;
}

int testFindMostCommonColour() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    int numNodesMinority = 2;

    //apply a colouring
    for(int n = 0; n < NUM_NODES - numNodesMinority; n++) {
        g[n]->colour = 1;
    }

    for(int n = NUM_NODES - numNodesMinority; n < NUM_NODES; n++) {
        g[n]->colour = 2;
    }

    //verify
    int mostCommon = findMostCommonColourInGraph(g, NUM_NODES, NUM_NODES + 1);
    if(mostCommon != 1) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}


int testFindNodeWithID() {
    //create a graph
    node** g = generateRandomGraph(NUM_NODES, 1);

    //verify
    node* identifiedNode = findNodeWithIdInGraph(g, NUM_NODES, NUM_NODES - 1);
    if(identifiedNode != g[NUM_NODES - 1]) return 1;

    freeGraph(g, NUM_NODES);

    return 0;
}
