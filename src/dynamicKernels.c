#include <stdlib.h>
#include <stdio.h>
#include "graphutil.h"
#include "dynamicKernels.h"

int possiblyRemoveEdgeKernel(node** graph, int numNodes, node* agent) {
    if(agent->degree > 0 && rand() % 1000 == 0) {
        removeEdge(agent, agent->neighbours[rand() % agent->degree]);
    }

    return numNodes;
}

int possiblyRemoveNodeKernel(node** graph, int numNodes, node* agent) {
    if(rand() % 100 == 0) {
        removeNode(&graph, sizeof(graph) / sizeof(node*), agent);
    }

    return numNodes;
}

int doubled = 0;

int doubleGraphSizeKernel(node** graph, int numNodes, node* agent) {
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