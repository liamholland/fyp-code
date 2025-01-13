#ifndef VISUAL
#define VISUAL

#include "node.h"

int traverseGraph(node** graph, int numNodes, node* focusNode, int nextNeighbour);

int printBlankMargin(int width);

int printNodeTwo(node* focusNode);

int printNodeThreeOrMore(node* focusNode, int middle);

int parseVisualisationCommand();

#endif