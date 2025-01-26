#ifndef DYNAMIC
#define DYNAMIC

#include "node.h"

int possiblyRemoveEdgeKernel(node** graph, int numNodes, node* agent);

int possiblyRemoveNodeKernel(node** graph, int numNodes, node* agent);

int doubleGraphSizeKernel(node** graph, int numNodes, node* agent);

#endif