#ifndef UTIL
#define UTIL

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

//appends an array of number of conflicts at iteration i to a csv file
//will create a file called "results.csv" if one does not already exist
int appendToResults(int* conflictArray, int numIterations);

//returns a boolean value indicating whether or not the given
//node is in conflict
//provides no information about the nature of the conflict
int nodeIsInConflict(node* node);

//returns an array of boolean values indicating whether or not each colour
//is present in the graph
int* findWhichColoursInGraph(node** graph, int numNodes, int maxColour);

//returns an array of nodes which are in conflict in the graph.
//functions by creating a copy of the graph and systematically moving
//all of the conflicting nodes to an array, while removing them and their
//neighbours from the graph copy so as to not waste time
node** findAllConflictingNodesInGraph(node** graph, int numNodes);

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
//removes the node and frees all of its memory, then reallocates the memory
//associated with the array, hence the pass by reference for the pointer
int removeNode(node*** graphReference, int numNodes, node* targetNode);

//adds an edge between the two provided nodes
int addEdgeBetweenNodes(node* nodeOne, node* nodeTwo);

//this function will return a pointer to the node with the highest degree
//in the case of a tie, the contender with the "largest colour" (least optimised)
//will be returned 
node* findNodeWithHighestDegree(node** graph, int numNodes);

//this function modifies the provided list and list length in order to remove
//the provided pointer from the list.
//the list length is modified because there could be any number of items removed
int removeAllInstancesOfNodePointerFromList(node*** nodeList, node* targetPointer, int* listLength);

//returns a vector of numbers representing how many times each colour
//appeared at in the graph
int* findColourFrequencies(node** graph, int numNodes, int maxColour);

//extension of findColourFrequencies which extracts the highest value in the graph
//will return the smallest colour if there is a tie
int findMostCommonColourInGraph(node** graph, int numNodes, int maxColour);

#endif