#ifndef MOVE
#define MOVE

/*
movement kernels will move an agent to another node
*/

#include "node.h"

//moves the agent to a random neighbour
//repeats numMoves times
node* randomMoveKernel(node* agent, int numMoves);

//moves to the first uncoloured neighbour it finds
//otherwise moves to the neighbour with the "largest" (least optimised) colour
//repeats numMoves times
node* optimalMoveKernel(node* agent, int numMoves);

#endif