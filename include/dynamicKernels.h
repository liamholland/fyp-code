#ifndef DYNAMIC
#define DYNAMIC

#include "node.h"

int possiblyRemoveEdgeKernel(node** graph, node* agent);

int possiblyRemoveNodeKernel(node** graph, node* agent);

int doubleGraphSizeKernel(node** graph, node* agent);

#endif