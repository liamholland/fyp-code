#ifndef DYNAMIC
#define DYNAMIC

/*
dynamic kernels which modify the topology of the graph based on some internal
criteria. these functions use triple pointers as references to the graph.
this is done due to the need to modify both the graph and the list of
agents operating on the graph; meaning we cannot simply return a new copy
of the freshly modified version of both lists. it is preferable to return the
number of changes regardless
*/

#include "node.h"

int possiblyRemoveEdgeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int possiblyRemoveNodeKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int removeOrphanNodesKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int removeNodeIfThereAreTooManyConflictsKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

int reduceAgentsInGraphKernel(node*** graphReference, int* numNodes, node* agent, node*** agentsReference, int* numAgents);

#endif