#ifndef DYNAMIC
#define DYNAMIC

#include "node.h"

int possiblyRemoveEdgeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int possiblyRemoveNodeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int removeOrphanNodesKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int removeNodeIfThereAreTooManyConflictsKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

#endif