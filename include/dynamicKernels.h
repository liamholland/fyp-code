#ifndef DYNAMIC
#define DYNAMIC

#include "node.h"

int possiblyRemoveEdgeKernel(node*** graphReference, int numNodes, node* agent);

int possiblyRemoveNodeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

#endif