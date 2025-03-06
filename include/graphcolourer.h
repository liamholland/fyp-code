#ifndef COLOURER
#define COLOURER

#include "node.h"

node** agentColour(node** graph, int* numNodesPtr, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, int save,
    int (*colouringKernel)(node* agent, int numNodes),
    int (*dynamicKernel)(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents),
    node* (*movementKernel)(node* agent, int numMoves));

node** pathColour(node** graph, int numNodes, node* firstStartingNode, node* secondStartingNode, int minColour, int maxColour, int save,
    int (*colouringKernel)(node**, int, int));

#endif