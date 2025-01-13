#ifndef VISUAL
#define VISUAL

int printGraph(node** graph, int numNodes);

int printBlankMargin(int width);

int printNodeOrphan(node* main);

int printNodeOne(node* main, node* other);

int printNodeTwo(node* main, node* first, node* second);

int printNodeThreeOrMore(node* main, node* first, node* middle, node* last);

int parseVisualisationCommand();

#endif