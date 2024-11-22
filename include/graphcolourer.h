#ifndef COLOURER
#define COLOURER

#include "node.h"

node** agentColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, int (*agentController)(node** agent, int numMoves, int numNodes), int save);

int colourblindFishAgent(node** fishPointer, int numMoves, int maxColour);

int minimumAgent(node** agentPointer, int numMoves, int maxColour);

int randomKernel(node** agentPointer, int numMoves, int maxColour);

#endif