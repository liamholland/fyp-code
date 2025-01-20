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
//an n greater than or equal to the number of nodes will return
//the pointer to the full graph
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

node** findAllConflictingNodesInGraph(node** graph, int numNodes);

node** findConflictingNeighboursForNode(node* n);

int removeEdge(node** nodeReference, node* neighbour);

#endif