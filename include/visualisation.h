#ifndef VISUAL
#define VISUAL

#include "node.h"

int traverseGraph(node** graph, int numNodes, node* focusNode, int nextNeighbour);

int normaliseColour(int colour);

int printBlankMargin(int width);

int printTraversalModeCommands();

int printNode(node* focusNode, int nextNeighbour);

int printNodeTwo(node* focusNode);

int printNodeThreeOrMore(node* focusNode, int middle);

#endif