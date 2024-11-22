#ifndef GENERATOR
#define GENERATOR

#include "node.h"

node** generateRingGraph(int numNodes);

node** generateRandomGraph(int numNodes, float p);

node** generateBipartiteGraph(int setOne, int setTwo);

#endif