#ifndef COLOURER
#define COLOURER

#include "node.h"

node** agentColour(node** graph, int* numNodesPtr, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, int save,
    int (*agentController)(node** agent, int numMoves, int numNodes),
    int (*dynamicKernel)(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents),
    node* (*movementKernel)(node* agent, int numMoves));

#endif