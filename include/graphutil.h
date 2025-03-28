#ifndef UTIL
#define UTIL

/*
these functions are helper functions used throughout the code base in order
to make common operations easier. their complexity varies.

note that two functions here are the only other places where triple-pointers
are used outside of the dynamic kernels. These are
- removeNode
- removeAllInstancesOfNodePointerFromList
the reason triple pointers are used is because the functions are written for use
specifically *in* the dynamic kernels. i did not want to make an entire copy of the
graph when removing nodes from it when these functions were going to be called a lot,
and the point of the dynamic kernels is to modify the lists anyway
*/


#include "node.h"

//initialises a whole load of node pointers.
//set the degree to 0 if you arent creating a graph that has
//the same degree for every node (e.g. bipartite graph)
node** initialiseGraph(int numNodes, int degree);

//prints out the data of every node in the graph in the format:
//node: [id]; colour: [c]; degree: [d]; neighbours: [neighbour ids] 
int printGraphAsText(node** graph, int numNodes);

//creates a copy of the graph
//this is a pointer to a new memory block with a copy of the data
node** copyGraph(node** graph, int numNodes);

//free all of the memory related to a graph
//deletes all of the nodes as well as the memory
//allocated to their neighbour arrays
int freeGraph(node** graph, int numNodes);

//allows you to apply a predetermined colouring to the nodes of the graph
//a colouring is just an array of integers representing colours
//does no error checking so make sure "colouring" is "numNodes" long
int applyColouring(node** graph, int* colouring, int numNodes);

//applies a colouring of 0 to every node in the graph
int resetGraphColours(node** graph, int numNodes);

//extracts a colour vector from a coloured graph
//a colour vector is a list of integers representing colours
int* extractGraphColours(node** graph, int numNodes);

//counts the number of unique colours present in the graph
int findNumColoursUsed(node** graph, int numNodes, int maxColour);

//finds the number of conflicts in the graph
//counts a conflict between each node once
int findNumConflicts(node** graph, int numNodes);

//counts the number of nodes in the graph that have not been
//assigned a colour
int findNumUncolouredNodes(node** graph, int numNodes);

//picks n unique nodes from the graph
//n is capped to the size of the graph (numNodes)
node** fetchNUniqueNodes(node** fullGraph, int numNodes, int n);

//returns a boolean value indicating whether or not the given
//node is in conflict
//provides no information about the nature of the conflict
int nodeIsInConflict(node* node);

//returns an array of boolean values indicating whether or not each colour
//is present in the graph
int* findWhichColoursInGraph(node** graph, int numNodes, int maxColour);

//finds the neighbour nodes which conflict with the provided node and
//returns them in an array
node** findConflictingNeighboursForNode(node* n);

//returns the number of conflicts that node n is under
int findNumberOfConflictsForNode(node* n);

//does what it says on the tin; removes the edge between the node
//and its neighbour
int removeEdge(node* nodeReference, node* neighbour);

//removes edges between the target node and all of its neighbours
//basically a convenience function; the amount of reallocation going
//on here guarantees that it is not optimal
int makeNodeOrpan(node* targetNode);

//yes that really is a `node***`
//it is better to use a triple pointer here rather than an expensive copy operation on every
//dyanmic kernel call. the copy would also require relocating the target node in
//the copied graph
//removes the node and frees all of its memory, then reallocates the memory
//associated with the array, hence the pass by reference for the pointer
int removeNode(node*** graphReference, int numNodes, node* targetNode);

//adds an edge between the two provided nodes
int addEdgeBetweenNodes(node* nodeOne, node* nodeTwo);

//this function will return a pointer to the node with the highest degree
//in the case of a tie, the contender with the "largest colour" (least optimised)
//will be returned 
node* findNodeWithHighestDegree(node** graph, int numNodes);

//similar to the previous, this function will find the node with the lowest degree
//in the case of a tie, the contender with the "largest colour" (least optimised)
//will be returned
node* findNodeWithLowestDegree(node** graph, int numNodes);

//this function modifies the provided list and list length in order to remove
//the provided pointer from the list
//uses references for a similar reason to the removeNode function
int removeAllInstancesOfNodePointerFromList(node*** nodeListReference, node* targetPointer, int* listLength);

//returns a vector of numbers representing how many times each colour
//appeared at in the graph
int* findColourFrequencies(node** graph, int numNodes, int maxColour);

//extension of findColourFrequencies which extracts the highest value in the graph
//will return the smallest colour if there is a tie
int findMostCommonColourInGraph(node** graph, int numNodes, int maxColour);

//returns a pointer to the node with the specified id in the graph
//returns NULL if the provided id was not found
node* findNodeWithIdInGraph(node** graph, int numNodes, int id);

#endif