#ifndef UTIL
#define UTIL

#include <stdlib.h>
#include "node.h"

node** initialiseGraph(int numNodes, int degree) {
    node** graph = (node**)malloc(sizeof(node*) * numNodes);

    //initialise all of the nodes
    for(int n = 0; n < numNodes; n++)
    {
        graph[n] = (node*)malloc(sizeof(node));
        graph[n]->id = n;
        graph[n]->colour = 0;   //0 is unassigned colour
        graph[n]->degree = degree;
        if(degree > 0) {
            graph[n]->neighbours = (node**)malloc(sizeof(node*) * graph[n]->degree);
        }
    }

    return graph;
}

// print each node in the graph
int printGraph(node** graph, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        printf("node: %d; colour: %d; degree: %d; neighbours: ", graph[i]->id, graph[i]->colour, graph[i]->degree);
        for(int nb = 0; nb < graph[i]->degree; nb++) {
            printf("%d ", graph[i]->neighbours[nb]->id);
        }
        printf("\n");
    }

    return 0;
}

// copy a graph
// all neighbour pointers are updated to point to the new block
node** copyGraph(node** graph, int numNodes) {
    node** graphcpy = (node**)malloc(sizeof(node*) * numNodes);

    //copy all of the nodes
    for(int n = 0; n < numNodes; n++) {
        graphcpy[n] = (node*)malloc(sizeof(node));
        memcpy(graphcpy[n], graph[n], sizeof(node));
    }

    //update the neighbours to point to the new array
    //do it after first loop so that all the nodes actually exist
    for(int n = 0; n < numNodes; n++) {
        graphcpy[n]->neighbours = (node**)malloc(sizeof(node*) * graphcpy[n]->degree);
        for(int nb = 0; nb < graphcpy[n]->degree; nb++) {
            graphcpy[n]->neighbours[nb] = graphcpy[graph[n]->neighbours[nb]->id];
        }
    }

    return graphcpy;
}

// free all of the memory used by a graph
int freeGraph(node** graph, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        free(graph[n]->neighbours); //dont have to free each member of neighbours since they are all in this array
        free(graph[n]);
    }

    free(graph);

    return 0;
}

int applyColouring(node** graph, int* colouring, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        graph[n]->colour = colouring[n];
    }

    return 0;
}

int resetGraphColours(node** graph, int numNodes) {
    int* zeroVector = (int*)malloc(sizeof(int) * numNodes);

    for(int i = 0; i < numNodes; i++) {
        zeroVector[i] = 0;
    }

    applyColouring(graph, zeroVector, numNodes);

    free(zeroVector);

    return 0;
}

int* extractGraphColours(node** graph, int numNodes) {
    int* colourVector = (int*)malloc(sizeof(int) * numNodes);

    for(int n = 0; n < numNodes; n++) {
        colourVector[n] = graph[n]->colour;
    }

    return colourVector;
}

int findNumColoursUsed(node** graph, int numNodes, int maxColour) {
    int numColours = 0;
    int* coloursSeen = (int*)malloc(sizeof(int) * maxColour);

    for(int i = 0; i < maxColour; i++) {
        coloursSeen[i] = 0;
    }

    for(int n = 0; n < numNodes; n++) {
        int c = graph[n]->colour;

        if(!coloursSeen[c - 1]) {
            coloursSeen[c - 1] = 1;
            numColours++;
        }
    }

    return numColours;
}

int findNumConflicts(node** graph, int numNodes) {
    int numConflicts = 0;

    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < graph[i]->degree; j++) {
            if(graph[i]->colour == graph[i]->neighbours[j]->colour && graph[i]->colour > 0) {
                // printf("conflict at %d->%d\n", graph[i]->id, graph[i]->neighbours[j]->id);
                numConflicts++;
            }
        }
    }

    return numConflicts / 2;    //each conflict is counted twice
}

int findNumUncolouredNodes(node** graph, int numNodes) {
    int numUncoloured = 0;

    for(int n = 0; n < numNodes; n++) {
        if(!graph[n]->colour) {
            numUncoloured++;
        }
    }

    return numUncoloured;
}

node** fetchNUniqueNodes(node** fullGraph, int numNodes, int n) {
    if(n >= numNodes) {
        return fullGraph;
    }
    
    node** nodes = (node**)malloc(sizeof(node*) * n);

    int* selectedIndex = (int*)malloc(sizeof(int) * numNodes);
    for(int i = 0; i < numNodes; i++) {
        selectedIndex[i] = 0;
    }

    //fetch random nodes
    for(int i = 0; i < n; i++) {
        int node;

        do {
            node = rand() % numNodes;
        }while(selectedIndex[node]);

        selectedIndex[node] = 1;
        nodes[i] = fullGraph[node];
    }

    free(selectedIndex);

    return nodes;
}

#endif