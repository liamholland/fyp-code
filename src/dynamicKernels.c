#include <stdlib.h>
#include <stdio.h>
#include "graphutil.h"
#include "dynamicKernels.h"

int possiblyRemoveEdgeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents) {
    if(agent->degree > 0 && rand() % 1000 == 0) {
        removeEdge(agent, agent->neighbours[rand() % agent->degree]);
    }

    return 0;
}

int possiblyRemoveNodeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents) {
    if(rand() % 1000 == 0) {
        removeNode(graphReference, *numNodes, agent);
        *numNodes -= 1;

        removeAllInstancesOfNodePointerFromList(agentsReference, agent, numAgents);
    }

    return 0;
}

int removeOrphanNodesKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents) {
    if(agent->degree == 0) {
        removeNode(graphReference, *numNodes, agent);
        *numNodes -= 1;

        removeAllInstancesOfNodePointerFromList(agentsReference, agent, numAgents);
    }

    return 0;
}
