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


int firstRound = 0; //counter to determine if we have already done a round of agents

int removeNodeIfThereAreTooManyConflictsKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents) {
    if(++firstRound > *numAgents) {
        node** conflictingNeighbours = findConflictingNeighboursForNode(agent);
        int numConflictingNeighbours = sizeof(conflictingNeighbours) / sizeof(node*);

        if(numConflictingNeighbours > (agent->degree / 2)) {
            removeNode(graphReference, *numNodes, agent);
            *numNodes -= 1;

            removeAllInstancesOfNodePointerFromList(agentsReference, agent, numAgents);
        }
    }
    
    return 0;
}