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

// generate a bipartite graph
// in this graph, there are two sets of nodes
// in each set, every node is connected to every node in the other set
// all nodes in a set are independent
node** generateBipartiteGraph(int setOne, int setTwo) {
    node** g1 = initialiseGraph(setOne + setTwo, setTwo);
    node** g2 = initialiseGraph(setTwo, setOne);

    //connect the nodes
    for(int n = 0; n < setOne; n++) {
        for(int nb = 0; nb < setTwo; nb++) {
            g1[n]->neighbours[nb] = g2[nb];
        }
    }

    for(int n = 0; n < setTwo; n++) {
        for(int nb = 0; nb < setOne; nb++) {
            g2[n]->neighbours[nb] = g1[nb];
        }
    }

    //add g2 to g1
    for(int n = setOne; n < setOne + setTwo; n++) {
        g1[n] = g2[n - setOne];
        g1[n]->id = n;
    }

    g2 = NULL;

    return g1;  //this pointer now points to the entire graph
}