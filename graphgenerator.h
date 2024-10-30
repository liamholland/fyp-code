#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "graphutil.h"

// generate a graph represented as an array of nodes
// a ring graph is a graph of n nodes where the degree of each node is 2
// in our representation, this means each node n has neighbours n-1, n+1 % numNodes
node** generateRingGraph(int numNodes) {
    node** graph = initialiseGraph(numNodes, 2);

    //once the graph is populated, connect the nodes together
    //each node in a ring graph is connected to the node before and after it
    for(int n = 0; n < numNodes; n++) {
        graph[n]->neighbours[0] = graph[(n - 1 + numNodes) % numNodes];
        graph[n]->neighbours[1] = graph[(n + 1) % numNodes];
    }

    return graph;
}

// generate a random graph
// each node has an edge to each other node, which has a
// percentage probability p that it exists
node** generateRandomGraph(int numNodes, float p) {
    srand((unsigned) time(NULL));
    
    //initialising 1 node pointer's worth of memory allows us to use realloc
    node** graph = initialiseGraph(numNodes, 1);

    //reset degrees for simplicity
    for(int n = 0; n < numNodes; n++) {
        graph[n]->degree = 0;
    }

    //iterate over half of the virtual edge matrix
    for(int n = 0; n < numNodes - 1; n++) {
        for(int nb = n + 1; nb < numNodes; nb++) {

            //each edge has a p% chance of existing
            if(rand() % 101 <= 100 * p) {
                graph[n]->neighbours = (node**)realloc(graph[n]->neighbours, sizeof(node*) * (graph[n]->degree + 1));
                graph[n]->neighbours[graph[n]->degree] = graph[nb];
                graph[n]->degree++;

                graph[nb]->neighbours = (node**)realloc(graph[nb]->neighbours, sizeof(node*) * (graph[nb]->degree + 1));
                graph[nb]->neighbours[graph[nb]->degree] = graph[n];
                graph[nb]->degree++;
            }
        }
    }

    return graph;
}