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

        node** agents = *agentsReference;

        //remove the pointer from the agents array if necessary
        removeNode(graphReference, *numNodes, agent);

        //multiple agents may have moved onto the node
        int countValidAgents = 0;
        node** remainingAgents = (node**)malloc(sizeof(node*) * (*numAgents));
        for(int a = 0; a < *numAgents; a++) {
            if(agents[a] != agent) {
                remainingAgents[countValidAgents++] = agents[a];
            }
        }

        remainingAgents = (node**)realloc(remainingAgents, sizeof(node*) * countValidAgents);
        free(agents);
        *agentsReference = remainingAgents;
        *numAgents = countValidAgents;

        //will only ever remove one node at a time
        *numNodes -= 1;
    }

    return 0;
}
