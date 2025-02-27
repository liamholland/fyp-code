#ifndef COLOURERS
#define COLOURERS

/*
colouring kernels will change the colour of a node, and move the agent to
a different node. noteably, these kernels are the only place in the program
where a node** is not an array of nodes, but a reference to a single node pointer.
this is necessary in order to allow the agent to "move" (i.e. point to a
different node)
*/

#include "node.h"

//KNOWLEDGE:    the agent (fish) only knows if it is conflict, but nothing about the conflict
//COLOURING:    if in conflict, the kernel increments the colour value of the node
int colourblindAgentIncrement(node* fish, int maxColour);

//KNOWLEDGE:    the agent (fish) only knows if it is conflict, but nothing about the conflict
//COLOURING:    if in conflict, the kernel decrements the colour value of the node
int colourblindAgentDecrement(node* fish, int maxColour);

//KNOWLEDGE:    the agent knows what colour is on the node, and the colours of all of its neighbours
//COLOURING:    the agent will find the lowest possible colour it can apply to the node, based on the colours in its locality
int minimumAgent(node* agent, int maxColour);

//KNOWLEDGE:    only knows if the node is in conflict or not
//COLOURING:    if the node is in conflict, picks a random colour between 1 and maxColour for the node
int randomKernel(node* agent, int maxColour);

//KNOWLEDGE:    only knows if the node is in conflict or not
//COLOURING:    if the node is uncoloured, applies the degree of the node as its colour, if in conflict,
// it will remove the edge between the node and the first conflict
int edgeChopperKernel(node* agent, int maxColour);

//KNOWLEDGE:    knows what colour is on the node, and the colours of its neighbours
//COLOURING:    the same as minimum local colour if it is a normal node, if it is an
//  imposter, it will colour the node with the colour that will cause the greatest number of conflicts
//MOVES:        same as minimum local colour, but this is untested behaviour and will likely not work
int amongUsKernel(node* agent, int maxColour);

#endif