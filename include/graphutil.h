#ifndef UTIL
#define UTIL

#include "node.h"

node** initialiseGraph(int numNodes, int degree);

int printGraphAsText(node** graph, int numNodes);

node** copyGraph(node** graph, int numNodes);

int freeGraph(node** graph, int numNodes);

int applyColouring(node** graph, int* colouring, int numNodes);

int resetGraphColours(node** graph, int numNodes);

int* extractGraphColours(node** graph, int numNodes);

int findNumColoursUsed(node** graph, int numNodes, int maxColour);

int findNumConflicts(node** graph, int numNodes);

int findNumUncolouredNodes(node** graph, int numNodes);

node** fetchNUniqueNodes(node** fullGraph, int numNodes, int n);

int appendToResults(int* conflictArray, int numIterations);

int nodeIsInConflict(node* node);

int* findWhichColoursInGraph(node** graph, int numNodes, int maxColour);

#endif