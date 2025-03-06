#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphutil.h"

node** initialiseGraph(int numNodes, int degree) {
    node** graph = (node**)malloc(sizeof(node*) * numNodes);

    //initialise all of the nodes
    for(int n = 0; n < numNodes; n++)
    {
        graph[n] = (node*)malloc(sizeof(node));
        graph[n]->id = n;
        graph[n]->colour = 0;   //0 is unassigned colour
        graph[n]->degree = degree;
        if(degree > 0) {
            graph[n]->neighbours = (node**)malloc(sizeof(node*) * graph[n]->degree);
        }
    }

    return graph;
}

int printGraphAsText(node** graph, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        printf("node: %d; colour: %d; degree: %d; neighbours: ", graph[i]->id, graph[i]->colour, graph[i]->degree);
        for(int nb = 0; nb < graph[i]->degree; nb++) {
            printf("%d ", graph[i]->neighbours[nb]->id);
        }
        printf("\n");
    }

    return 0;
}

node** copyGraph(node** graph, int numNodes) {
    node** graphcpy = (node**)malloc(sizeof(node*) * numNodes);

    //copy all of the nodes
    for(int n = 0; n < numNodes; n++) {
        graphcpy[n] = (node*)malloc(sizeof(node));
        memcpy(graphcpy[n], graph[n], sizeof(node));
    }

    int* differentials = (int*)calloc(numNodes, sizeof(int));
    if(numNodes - graph[numNodes - 1]->id != 0) {
        //graph indexes do not line up with ids, calculate differentials
        int differential = 0;
        int nodesTraversed = 0;

        for(int n = 0; n < numNodes; n++) {
            differentials[n] += graph[n]->id - nodesTraversed++;
        }
    }

    //update the neighbours to point to the new array
    //do it after first loop so that all the nodes actually exist
    for(int n = 0; n < numNodes; n++) {
        graphcpy[n]->neighbours = (node**)malloc(sizeof(node*) * graphcpy[n]->degree);
        for(int nb = 0; nb < graphcpy[n]->degree; nb++) {
            int neighbourId = graph[n]->neighbours[nb]->id;
            graphcpy[n]->neighbours[nb] = graphcpy[neighbourId - differentials[neighbourId]];
        }
    }

    free(differentials);

    return graphcpy;
}

int freeGraph(node** graph, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        free(graph[n]->neighbours); //dont have to free each member of neighbours since they are all in this array
        free(graph[n]);
        graph[n] == NULL;
    }

    free(graph);

    return 0;
}

int applyColouring(node** graph, int* colouring, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        graph[n]->colour = colouring[n];
    }

    return 0;
}

int resetGraphColours(node** graph, int numNodes) {
    int* zeroVector = (int*)calloc(numNodes, sizeof(int));

    applyColouring(graph, zeroVector, numNodes);

    free(zeroVector);

    return 0;
}

int* extractGraphColours(node** graph, int numNodes) {
    int* colourVector = (int*)malloc(sizeof(int) * numNodes);

    for(int n = 0; n < numNodes; n++) {
        colourVector[n] = graph[n]->colour;
    }

    return colourVector;
}

int findNumColoursUsed(node** graph, int numNodes, int maxColour) {
    int numColours = 0;
    int* coloursSeen = (int*)calloc(maxColour, sizeof(int));

    for(int n = 0; n < numNodes; n++) {
        int c = graph[n]->colour;

        if(!coloursSeen[c - 1]) {
            coloursSeen[c - 1] = 1;
            numColours++;
        }
    }

    return numColours;
}

int findNumConflicts(node** graph, int numNodes) {
    int numConflicts = 0;

    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < graph[i]->degree; j++) {
            if(graph[i]->colour == graph[i]->neighbours[j]->colour && graph[i]->colour > 0) {
                // printf("conflict at %d->%d\n", graph[i]->id, graph[i]->neighbours[j]->id);
                numConflicts++;
            }
        }
    }

    return numConflicts / 2;    //each conflict is counted twice
}

int findNumUncolouredNodes(node** graph, int numNodes) {
    int numUncoloured = 0;

    for(int n = 0; n < numNodes; n++) {
        if(!graph[n]->colour) {
            numUncoloured++;
        }
    }

    return numUncoloured;
}

node** fetchNUniqueNodes(node** fullGraph, int numNodes, int n) {
    if(n > numNodes) {
        n = numNodes;   //cannot create more agents than nodes
    }

    node** nodes = (node**)malloc(sizeof(node*) * n);

    int* selectedIndex = (int*)calloc(numNodes, sizeof(int));

    //fetch random nodes
    for(int i = 0; i < n; i++) {
        int node;

        do {
            node = rand() % numNodes;
        }while(selectedIndex[node]);

        selectedIndex[node] = 1;
        nodes[i] = fullGraph[node];
    }

    free(selectedIndex);

    return nodes;
}

int nodeIsInConflict(node* n) {
    for(int nb = 0; nb < n->degree; nb++) {
        if(n->colour == n->neighbours[nb]->colour && n->neighbours[nb]->colour > 0) {
            return 1;
        }
    }

    return 0;
}

int* findWhichColoursInGraph(node** graph, int numNodes, int maxColour) {
    int* colourTruthVector = (int*)calloc(maxColour, sizeof(int));

    for(int n = 0; n < numNodes; n++) {
        colourTruthVector[graph[n]->colour] = 1;
    }

    return colourTruthVector;
}

node** findAllConflictingNodesInGraph(node** graph, int numNodes) {
    node** conflictingNodes = (node**)malloc(numNodes * sizeof(node*));

    int totalNumConflictingNodes = 0;

    node** graphCopy = copyGraph(graph, numNodes);

    for(int i = 0; i < numNodes; i++) {
        if(graphCopy[i] == NULL) continue;

        node** conflicts = findConflictingNeighboursForNode(graphCopy[i]);
        
        if(conflicts == NULL) continue;

        int numConflicts = sizeof(conflicts) / sizeof(node*);

        memcpy(conflictingNodes[totalNumConflictingNodes], conflicts, sizeof(node*) * numConflicts);

        totalNumConflictingNodes += numConflicts;

        freeGraph(conflicts, numConflicts); //this should make the pointers null in the graph copy
    }

    freeGraph(graphCopy, numNodes);

    return conflictingNodes;
}

node** findConflictingNeighboursForNode(node* n) {
    node** conflictingNodes = (node**)malloc(n->degree * sizeof(node*));

    int numConflictingNodes = 0;

    for(int i = 0; i < n->degree; i++) {
        if(n->colour == n->neighbours[i]->colour) {
            conflictingNodes[numConflictingNodes++] = n->neighbours[i];
        }
    }

    if(numConflictingNodes == 0) {
        free(conflictingNodes);
        return NULL;
    }

    return (node**)realloc(conflictingNodes, numConflictingNodes * sizeof(numConflictingNodes));
}

int removeEdge(node* nodeReference, node* neighbourReference) {
    int foundNeighbour = 0;

    for(int i = 0; i < nodeReference->degree; i++) {
        if(nodeReference->neighbours[i] == neighbourReference) {
            foundNeighbour = 1;
            
            //move each neighbour up one
            for(int j = i; j < nodeReference->degree - 1; j++) {
                nodeReference->neighbours[j] = nodeReference->neighbours[j + 1];
            }

            nodeReference->neighbours[nodeReference->degree - 1] = NULL;  //remove the last pointer
            nodeReference->neighbours = (node**)realloc(nodeReference->neighbours, sizeof(node*) * (nodeReference->degree - 1));   //reduce the memory in the struct
            nodeReference->degree--;

            break;
        }
    }
    
    if(!foundNeighbour) {
        return 1;   //did not find the neighbour
    }

    for(int i = 0; i < neighbourReference->degree; i++) {
        if(neighbourReference->neighbours[i] == nodeReference) {
            //move each neighbour up one
            for(int j = i; j < neighbourReference->degree - 1; j++) {
                neighbourReference->neighbours[j] = neighbourReference->neighbours[j + 1];
            }

            neighbourReference->neighbours[neighbourReference->degree - 1] = NULL;  //remove the last pointer
            neighbourReference->neighbours = (node**)realloc(neighbourReference->neighbours, sizeof(node*) * (neighbourReference->degree - 1));   //reduce the memory in the struct
            neighbourReference->degree--;

            return 0;
        }
    }

    return 1;
}

int makeNodeOrpan(node* targetNode) {
    //for each neighbour
    for(int n = 0; n < targetNode->degree; n++) {
        //remove targetNode reference from the neighbour
        node* neighbour = targetNode->neighbours[n];

        for(int i = 0; i < neighbour->degree; i++) {
            if(neighbour->neighbours[i] == targetNode) {
                for(int j = i; j < neighbour->degree - 1; j++) {
                    neighbour->neighbours[j] = neighbour->neighbours[j + 1];
                }

                neighbour->neighbours[neighbour->degree - 1] = NULL;
                neighbour->neighbours = (node**)realloc(neighbour->neighbours, sizeof(node*) * (neighbour->degree - 1));
                neighbour->degree -= 1;

                break;
            }
        }
    }

    //remove all neighbours from targetNode
    for(int n = 0; n < targetNode->degree; n++) {
        targetNode->neighbours[n] = NULL;
    }

    targetNode->neighbours = NULL;
    targetNode->degree = 0;
    free(targetNode->neighbours);

    return 0;
}

int removeNode(node*** graphReference, int numNodes, node* targetNode) {
    if(targetNode == NULL) {
        return 1;
    }
    
    makeNodeOrpan(targetNode);

    node** graph = *graphReference;

    //find the nodes position in the array
    //cant rely on id since other nodes might have been removed
    int n;
    for(n = 0; n < numNodes; n++) {
        if(graph[n] == targetNode) break;
    }

    //free the memory
    free(targetNode->neighbours);
    free(targetNode);
    targetNode = NULL;

    //move all of the nodes up one
    for(int i = n; i < numNodes - 1; i++) {
        graph[i] = graph[i + 1];
    }

    //reallocate memory
    (*graphReference) = (node**)realloc(*graphReference, sizeof(node*) * (numNodes - 1));

    return 0;
}

int addEdgeBetweenNodes(node* nodeOne, node* nodeTwo) {
    nodeOne->neighbours = (node**)realloc(nodeOne->neighbours, sizeof(node*) * ++(nodeOne->degree));
    nodeOne->neighbours[nodeOne->degree - 1] = nodeTwo;
    
    nodeTwo->neighbours = (node**)realloc(nodeTwo->neighbours, sizeof(node*) * ++(nodeTwo->degree));
    nodeTwo->neighbours[nodeTwo->degree - 1] = nodeOne;

    return 0;
}

node* findNodeWithHighestDegree(node** graph, int numNodes) {
    int highestDegree = 0;
    node** highestDegreeContenders = (node**)malloc(sizeof(node*) * numNodes);
    int numContenders = 0;

    for(int n = 0; n < numNodes; n++) {
        if(graph[n]->degree > highestDegree) {
            highestDegree = graph[n]->degree;
            numContenders = 1;
            highestDegreeContenders[0] = graph[n];
        }
        else if(graph[n]->degree == highestDegree) {
            highestDegreeContenders[numContenders++] = graph[n];
        }
    }

    if(numContenders == 0) {
        free(highestDegreeContenders);
        return graph[0];    //all nodes are orphans
    }
    
    //in the case of a tie, return the node with the highest colour
    if(numContenders > 1) {
        int highestColour = -1; //worst case, the first contender will be returned
        node* highestColourNode;

        for(int n = 0; n < numContenders; n++) {
            if(highestDegreeContenders[n]->colour > highestColour) {
                highestColour = highestDegreeContenders[n]->colour;
                highestColourNode = highestDegreeContenders[n];
            }
        }

        free(highestDegreeContenders);
        return highestColourNode;
    }

    //only one contender
    node* highestDegreeNode = highestDegreeContenders[0];
    free(highestDegreeContenders);
    return highestDegreeNode;
}

node* findNodeWithLowestDegree(node** graph, int numNodes) {
    int lowestDegree = 0;
    node** lowestDegreeContenders = (node**)malloc(sizeof(node*) * numNodes);
    int numContenders = 0;

    for(int n = 0; n < numNodes; n++) {
        if(graph[n]->degree < lowestDegree) {
            lowestDegree = graph[n]->degree;
            numContenders = 1;
            lowestDegreeContenders[0] = graph[n];
        }
        else if(graph[n]->degree == lowestDegree) {
            lowestDegreeContenders[numContenders++] = graph[n];
        }
    }

    if(numContenders == 0) {
        free(lowestDegreeContenders);
        return graph[0];    //all nodes are orphans
    }
    
    //in the case of a tie, return the node with the highest colour
    if(numContenders > 1) {
        int highestColour = -1; //worst case, the first contender will be returned
        node* highestColourNode;

        for(int n = 0; n < numContenders; n++) {
            if(lowestDegreeContenders[n]->colour > highestColour) {
                highestColour = lowestDegreeContenders[n]->colour;
                highestColourNode = lowestDegreeContenders[n];
            }
        }

        free(lowestDegreeContenders);
        return highestColourNode;
    }

    //only one contender
    node* lowestDegreeNode = lowestDegreeContenders[0];
    free(lowestDegreeContenders);
    return lowestDegreeNode;
}

int removeAllInstancesOfNodePointerFromList(node*** nodeListReference, node* targetPointer, int* listLength) {
    node** list = *nodeListReference;
    
    int countValidAgents = 0;
    node** remainingAgents = (node**)malloc(sizeof(node*) * (*listLength));
    for(int n = 0; n < *listLength; n++) {
        if(list[n] != targetPointer) {
            remainingAgents[countValidAgents++] = list[n];
        }
    }

    remainingAgents = (node**)realloc(remainingAgents, sizeof(node*) * countValidAgents);
    free(list);
    *nodeListReference = remainingAgents;
    *listLength = countValidAgents;

    return 0;
}

int* findColourFrequencies(node** graph, int numNodes, int maxColour) {
    int* colourFreqVector = (int*)calloc(maxColour, sizeof(int));

    for(int n = 0; n < numNodes; n++) {
        colourFreqVector[graph[n]->colour]++;
    }

    return colourFreqVector;
}

int findMostCommonColourInGraph(node** graph, int numNodes, int maxColour) {
    int* colourFreqVector = findColourFrequencies(graph, numNodes, maxColour);

    int mostCommonColour = 0;
    for(int i = 0; i < maxColour; i++) {
        if(colourFreqVector[i] > mostCommonColour) {
            mostCommonColour = i;
        }
    }

    free(colourFreqVector);

    return mostCommonColour;
}

node* findNodeWithIdInGraph(node** graph, int numNodes, int id) {
    for(int n = 0; n < numNodes; n++) {
        if(graph[n]->id == id) {
            return graph[n];
        }
    }

    return NULL;
}