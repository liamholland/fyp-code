#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graphutil.h"

#define AGENT_PERC_LIMIT 10
#define AGENT_BREAK_LIMIT 50

// this literally just has each node choose a random colour between 1 and the max colour (== numNodes)
// however, it only changes its colour if it is conflicting with its neighbours
// it continues until there were no conflicts or the cutoff of maxIterations
// the current implementation will not necessarily find the best solution, but the one before the first failure
node** imFeelingLuckyColour(node** graph, int numNodes, int maxIterations) {
    int maxColour = numNodes;   //the ultimate maximum is a different colour for every node

    node** colouringGraph = copyGraph(graph, numNodes);     //this graph is used to find colouring solutions
    int* lastBestSolution = extractGraphColours(colouringGraph, numNodes);   //array to store colouring solutions. centralised?

    while(maxColour > 0) {
        int anyConflicts = 0;

        //random colour
        for(int i = 0; i < maxIterations; i++) {
            anyConflicts = 0;

            for(int n = 0; n < numNodes; n++) {

                for(int nb = 0; nb < colouringGraph[n]->degree; nb++) {

                    //if the neighbour colour matches the node colour or the node has not been assigned a colour
                    if(colouringGraph[n]->neighbours[nb]->colour == colouringGraph[n]->colour || !colouringGraph[n]->colour) {
                        colouringGraph[n]->colour = rand() % maxColour + 1;
                        anyConflicts = 1;
                        break;
                    }
                }
            }

            //stopping condition for random colour
            if(!anyConflicts) {
                break;
            }
        }

        if(!anyConflicts) {
            free(lastBestSolution);
            lastBestSolution = extractGraphColours(colouringGraph, numNodes);
        }
        else {
            break;
        }
        resetGraphColours(colouringGraph, numNodes);    //reset colouring graph
        maxColour--;
    }

    applyColouring(colouringGraph, lastBestSolution, numNodes);

    free(lastBestSolution);

    printf("final max colour: %d\n", maxColour + 1);    //+1 because the current max was the attempt that did not work
    
    // UNCOMMENT THE BELOW LINE TO VERIFY EVERY COLOUR FROM 1..(maxColour + 1) IS USED IN THE COLOURING
    // printf("chromatic colour: %d\n", findNumColoursUsed(lastBestSolution, numNodes, maxColour + 1)); 

    return colouringGraph;
}

// inspired by ant colouring algorithms, although this algorithm has no "intelligence"
// the agents (fish) move between the nodes blindly, making no distinction as to whether they have been there recently
// if the fish lands on a node that is conflicting, try the next colour in the range 1..deg(n)
// the nodes are initially coloured with the colour equalling their degree
node** shortsightedGoldfishColour(node** graph, int numNodes, int maxIterations, int numFish, int numMoves) {
    node** colouringGraph = copyGraph(graph, numNodes);
    int* initColouring = (int*)malloc(sizeof(int) * numNodes);

    //create an initial colouring
    for(int k = 0; k < numNodes; k++) {
        initColouring[k] = graph[k]->degree;    //degree of each node
    }

    applyColouring(colouringGraph, initColouring, numNodes);

    free(initColouring);

    int* conflictsAtIterationI = (int*)malloc(sizeof(int) * maxIterations);

    int numNoChangesPerculate = 0;    //if no agent makes a change in x iterations, we move them all around
    int numNoChangesBreak = 0;      //if no agent makes a change in x iterations, the algorithm ends

    //pick some starting nodes for the "fish"
    node** fish = fetchNUniqueNodes(colouringGraph, numNodes, numFish);

    //start the iterations
    int i;
    for(i = 0; i < maxIterations; i++) {
        int numChanges = 0;

        //each "fish" makes changes to the graph
        for(int f = 0; f < numFish; f++) {

            //check for conflicts in neighbours
            if(!fish[f]->colour || nodeIsInConflict(fish[f])) {
                fish[f]->colour = (fish[f]->colour + 1) % (fish[f]->degree + 1);

                if(!fish[f]->colour) {
                    fish[f]->colour++;
                }

                numChanges++;
            }

            //the fish wanders in its locality
            for(int m = 0; m < numMoves; m++) {
                fish[f] = fish[f]->neighbours[rand() % fish[f]->degree];
            }
        }
        
        conflictsAtIterationI[i] = findNumConflicts(colouringGraph, numNodes);

        if(!numChanges) {
            numNoChangesPerculate++;
            if(numNoChangesPerculate == AGENT_PERC_LIMIT) {     // == because i only want this to happen on that iteration
                free(fish);
                fish = fetchNUniqueNodes(colouringGraph, numNodes, numFish);
            }

            numNoChangesBreak++;
            if(numNoChangesBreak == AGENT_BREAK_LIMIT) {
                printf("no changes after %d iterations\n", i);
                break;
            }
        }
        else{
            numNoChangesPerculate = 0;
            numNoChangesBreak = 0;
        }
    }

    printf("number of agents: %d; number of colours: %d; number of conflicts: %d; number of missed nodes: %d\n", 
        numFish, findNumColoursUsed(colouringGraph, numNodes, numNodes), findNumConflicts(colouringGraph, numNodes), findNumUncolouredNodes(colouringGraph, numNodes));

    // write to csv file
    appendToResults(conflictsAtIterationI, i);

    free(conflictsAtIterationI);
    free(fish); //hopefully to their natural habitat :)

    return colouringGraph;
}

// inspired by the centralised minimum (greedy) colour
// gets much closer to the chromatic colour than shortsighted goldfish
// applies the minimum colour possible to a node based on the colours of its neighbours
// moves the agents based on two goals - move to the first uncoloured node you find in the neighbours,
// or move to the node in the current nodes neighbours with the highest colour
node** agentMinimumColour(node** graph, int numNodes, int maxIterations, int numAgents, int numMoves) {
    node** colouringGraph = copyGraph(graph, numNodes);

    node** agents = fetchNUniqueNodes(colouringGraph, numNodes, numAgents);

    int numNoChangesPerculate = 0;    //if no agent makes a change in x iterations, we move them all around
    int numNoChangesBreak = 0;      //if no agent makes a change in x iterations, the algorithm ends

    int i;
    for(i = 0; i < maxIterations; i++) {
        int numChanges = 0;

        for(int a = 0; a < numAgents; a++) {

            if(!agents[a]->colour || nodeIsInConflict(agents[a])) {
                int* coloursInLocality = findWhichColoursInGraph(agents[a]->neighbours, agents[a]->degree, numNodes);

                coloursInLocality[agents[a]->colour] = 1;

                for(int c = 1; c < numNodes; c++) {
                    if(!coloursInLocality[c]) {
                        agents[a]->colour = c;
                    }
                }

                numChanges++;
            }

            //move the agent
            for(int m = 0; m < numMoves; m++) {
                if(findNumUncolouredNodes(agents[a]->neighbours, agents[a]->degree) > 0) {
                    for(int nb = 0; nb < agents[a]->degree; nb++) {
                        if(!agents[a]->neighbours[nb]->colour) {
                            agents[a] = agents[a]->neighbours[nb];
                        }
                    }
                }
                else {
                    if(agents[a]->degree == 0) {
                        break;  //cant move the agent; on an orphan node
                    }

                    node* maxColourNode = agents[a]->neighbours[0];
                    for(int nb = 0; nb < agents[a]->degree; nb++) {
                        if(agents[a]->neighbours[nb]->colour > maxColourNode->colour) {
                            maxColourNode = agents[a]->neighbours[nb];
                        }
                    }

                    agents[a] = maxColourNode;
                }
            }
        }

        if(!numChanges) {
            numNoChangesPerculate++;
            if(numNoChangesPerculate == AGENT_PERC_LIMIT) {     // == because i only want this to happen on that iteration
                free(agents);
                agents = fetchNUniqueNodes(colouringGraph, numNodes, numAgents);
            }

            numNoChangesBreak++;
            if(numNoChangesBreak == AGENT_BREAK_LIMIT) {
                printf("no changes after %d iterations\n", i);
                break;
            }
        }
        else{
            numNoChangesPerculate = 0;
            numNoChangesBreak = 0;
        }
    }

    printf("number of agents: %d; number of colours: %d; number of conflicts: %d; number of missed nodes: %d\n", 
        numAgents, findNumColoursUsed(colouringGraph, numNodes, numNodes), findNumConflicts(colouringGraph, numNodes), findNumUncolouredNodes(colouringGraph, numNodes));

    free(agents);

    return colouringGraph;
}