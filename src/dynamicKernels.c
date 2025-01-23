#include <stdlib.h>
#include "graphutil.h"
#include "dynamicKernels.h"

int possiblyRemoveEdgeKernel(node** graph, node* agent) {
    if(agent->degree > 0 && rand() % 10 == 0) {
        removeEdge(agent, agent->neighbours[rand() % agent->degree]);
    }

    return 0;
}

int possiblyRemoveNodeKernel(node**, node* agent) {
    if(rand() % 100 == 0) {
        //remove the node outright
    }
    
    return 0;
}

int doubleGraphSizeKernel(node** graph, node* agent) {
    node** secondGraph = copyGraph(graph, sizeof(graph) / sizeof(node*));

    addEdgeBetweenNodes(graph[0], secondGraph[0]);

    return 0;
}