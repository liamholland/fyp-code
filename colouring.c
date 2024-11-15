#include <stdio.h>
#include <time.h>
#include <string.h>
#include "graphgenerator.h"
#include "graphcolourer.h"
#include "centralisedgraphcolouring.h"
#include "node.h"
#include "graphutil.h"

int main(int argc, char const *argv[]) {
    srand((unsigned) time(NULL));

    int numNodes = 10;
    char generator = 'r';
    int verbose = 0;
    int autoRuns = 1;

    //random colour
    int maxIterations = 100;

    //agent colour
    int numAgents = 5;
    int numMoves = 1;

    //random generator
    float prob = 0.5;

    //bipartite generator
    int nodesInSetOne = 0;

    for(int i = 0; i < argc; i++) {
        if(!(*argv[i] == '-')) {
            continue;
        }
        
        if(!strcmp(argv[i], "-n")) {
            numNodes = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-M")) {
            maxIterations = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-p")) {
            prob = atof(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-a")) {
            numAgents = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-m")) {
            numMoves = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-A")) {
            autoRuns = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-v")) {
            verbose = 1;
        }
        else if(!strcmp(argv[i], "-s")) {
            nodesInSetOne = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-g")) {
            generator = *argv[i + 1];
        }
    }

    node** graph;
    node** colouredGraph;
    node** chromaticallyColouredGraph;
    for(int a = 0; a < autoRuns; a++) {
        //generate the graph
        switch (generator) {
        case 'r':
            graph = generateRandomGraph(numNodes, prob);
            break;
        case 'o':
            graph = generateRingGraph(numNodes);
            break;
        case 'b':
            graph = generateBipartiteGraph(
                nodesInSetOne ? nodesInSetOne : numNodes / 2,
                nodesInSetOne ? numNodes - nodesInSetOne : numNodes - (numNodes / 2)
            );
            break;
        default:
            printf("invalid generator");
            return 1;
        }

        //colour the graph
        colouredGraph = agentColour(graph, numNodes, maxIterations, numAgents, numMoves, &smartAgent);
        chromaticallyColouredGraph = minimumColour(graph, numNodes);

        if(verbose) {
            printGraph(colouredGraph, numNodes);
            printf("\n");
            printGraph(chromaticallyColouredGraph, numNodes);
        }

        //free memory
        freeGraph(graph, numNodes);
        freeGraph(colouredGraph, numNodes);
        freeGraph(chromaticallyColouredGraph, numNodes);
    }

    return 0;
}