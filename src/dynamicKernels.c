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
        node** graph = *graphReference;
        node** agents = *agentsReference;

        //remove the pointer from the agents array if necessary
        if(graph != agents) {
            for(int i = 0; i < *numAgents; i++) {
                if(agents[i] == agent) {
                    for(int j = i; j < (*numAgents - 1); j++) {
                        agents[j] = agents[j + 1];
                    }

                    agents[*numAgents - 1] = NULL;
                    *agentsReference = (node**)realloc(*agentsReference, sizeof(node*) * (*numAgents - 1));

                    break;
                }
            }
        }

        removeNode(graphReference, *numNodes, agent);

        *numNodes = *numNodes - 1;
        *numAgents = *numAgents - 1;
    }


    return 0;
}
