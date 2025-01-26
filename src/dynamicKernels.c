#include <stdlib.h>
#include <stdio.h>
#include "graphutil.h"
#include "dynamicKernels.h"

int possiblyRemoveEdgeKernel(node** graph, int numNodes, node* agent) {
    if(agent->degree > 0 && rand() % 1000 == 0) {
        removeEdge(agent, agent->neighbours[rand() % agent->degree]);
    }

    return 0;
}

int possiblyRemoveNodeKernel(node** graph, int numNodes, node* agent) {
    if(rand() % 1000 == 0) {
        removeNode(&graph, numNodes, agent);
        return -1;
    }

    return 0;
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

        return numNodes;
    }

    return 0;
}