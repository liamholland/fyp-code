#include <stdlib.h>
#include <stdio.h>
#include "graphutil.h"
#include "dynamicKernels.h"

int possiblyRemoveEdgeKernel(node** graph, node* agent) {
    if(agent->degree > 0 && rand() % 10 == 0) {
        removeEdge(agent, agent->neighbours[rand() % agent->degree]);
    }

    return 0;
}

int possiblyRemoveNodeKernel(node** graph, node* agent) {
    if(rand() % 100 == 0) {
        removeNode(&graph, sizeof(graph) / sizeof(node*), agent);
    }

    return 0;
}

int doubled = 0;

int doubleGraphSizeKernel(node** graph, node* agent) {
    int numNodes = sizeof(graph) / sizeof(node*);
    if(!doubled && rand() % 1000 == 0) {
        node** secondGraph = copyGraph(graph, numNodes);

        //modify the new node ids
        for(int n = 0; n < numNodes; n++) {
            secondGraph[n]->id += numNodes;
        }

        addEdgeBetweenNodes(graph[0], secondGraph[0]);

        doubled = 1;
        numNodes *= 2;

        printf("made dynamic change\n");
    }

    return numNodes;
}