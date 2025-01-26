#ifndef COLOURER
#define COLOURER

#include "node.h"

node** agentColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves, int minColour, int maxColour, 
    int (*agentController)(node** agent, int numMoves, int numNodes), int (*dynamicKernel)(node** graph, int numNodes, node* agent), int save);

int colourblindFishAgentIncrement(node** fishPointer, int numMoves, int maxColour);

int colourblindFishAgentDecrement(node** fishPointer, int numMoves, int maxColour);

int minimumAgent(node** agentPointer, int numMoves, int maxColour);

int randomKernel(node** agentPointer, int numMoves, int maxColour);

int edgeChopperKernel(node** agentPointer, int numMoves, int maxColour);

#endif