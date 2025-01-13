#ifndef VISUAL
#define VISUAL

#include "node.h"

int traverseGraph(node** graph, int numNodes, node* focusNode);

int printBlankMargin(int width);

int printNodeOrphan(node* main);

int printNodeOne(node* main, node* other);

int printNodeTwo(node* main, node* first, node* second);

int printNodeThreeOrMore(node* main, node* first, node* middle, node* last);

int parseVisualisationCommand();

#endif