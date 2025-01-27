#ifndef COLOURERS
#define COLOURERS

#include "node.h"

//KNOWLEDGE:    the agent (fish) only knows if it is conflict, but nothing about the conflict
//COLOURING:    if in conflict, the kernel increments the colour value of the node
//MOVES:        moves to a random neighbour on each move
int colourblindFishAgentIncrement(node** fishPointer, int numMoves, int maxColour);

//KNOWLEDGE:    the agent (fish) only knows if it is conflict, but nothing about the conflict
//COLOURING:    if in conflict, the kernel decrements the colour value of the node
//MOVES:        moves to a random neighbour on each move
int colourblindFishAgentDecrement(node** fishPointer, int numMoves, int maxColour);

//KNOWLEDGE:    the agent knows what colour is on the node, and the colours of all of its neighbours
//COLOURING:    the agent will find the lowest possible colour it can apply to the node, based on the colours in its locality
//MOVES:        the agent moves to an uncoloured neighbour, or else to the neighbour with the "largest" colour
int minimumAgent(node** agentPointer, int numMoves, int maxColour);

//KNOWLEDGE:    only knows if the node is in conflict or not
//COLOURING:    if the node is in conflict, picks a random colour between 1 and maxColour for the node
//MOVES:        moves the agent to a random neighbour
int randomKernel(node** agentPointer, int numMoves, int maxColour);

//KNOWLEDGE:    only knows if the node is in conflict or not
//COLOURING:    if the node is uncoloured, applies the degree of the node as its colour, if in conflict,
// it will remove the edge between the node and the first conflict
//MOVES:        moves the agent to a random neighbour
int edgeChopperKernel(node** agentPointer, int numMoves, int maxColour);

#endif