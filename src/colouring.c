#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "graphgenerator.h"
#include "graphcolourer.h"
#include "centralisedgraphcolouring.h"
#include "graphutil.h"

#define HELP_FILE_NAME "help.txt"

int printHelp();

int main(int argc, char const *argv[]) {
    srand((unsigned) time(NULL));

    int numNodes = 10;
    char generator = 'r';
    int verbose = 0;
    int autoRuns = 1;
    int maxIterations = 50000;
    int save = 0;   //boolean flag to save results to a csv file
    int minColour = 0;
    int maxColour = 0;

    //agent colour
    int numAgents = 0;
    int numMoves = 0;

    //random generator
    float prob = 0.5;

    //bipartite generator
    int nodesInSetOne = 0;

    //CONSIDER: so many string comparisons; no better way?
    for(int i = 0; i < argc; i++) {
        if(!(*argv[i] == '-')) {
            continue;
        }
        
        if(!strcmp(argv[i], "-h")) {
            printHelp();
            return 0;
        }
        else if(!strcmp(argv[i], "-n")) {
            numNodes = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-M")) {
            maxIterations = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-p")) {
            prob = atof(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-c")) {
            minColour = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-C")) {
            maxColour = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-S")) {
            save = 1;
        }
        else if(!strcmp(argv[i], "-A")) {
            autoRuns = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-a")) {
            numAgents = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-m")) {
            numMoves = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-v")) {
            verbose = 1;
        }
        else if(!strcmp(argv[i], "-g")) {
            generator = *argv[i + 1];
        }
        else if(!strcmp(argv[i], "-s")) {
            nodesInSetOne = atoi(argv[i + 1]);
        }
    }

    //set defaults that are based on number of nodes

    if(!minColour) {
        minColour = numNodes + 1;
    }

    if(!numAgents) {
        numAgents = numNodes;
    }

    int useBenchmark = !maxColour ? 1 : 0;

    //graph variables
    node** graph;
    node** colouredGraph;
    node** benchmarkMinimumGraph;

    //run main program loop
    //remember default for this is to run once
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
        benchmarkMinimumGraph = minimumColour(graph, numNodes);
        
        if(useBenchmark) {
            maxColour = findNumColoursUsed(benchmarkMinimumGraph, numNodes, numNodes + 1);
        }

        colouredGraph = agentColour(graph, numNodes, maxIterations, numAgents, numMoves, minColour, maxColour + 1, &minimumAgent, save);

        if(verbose) {
            printGraph(colouredGraph, numNodes);
            printf("\n");
            printGraph(benchmarkMinimumGraph, numNodes);
        }

        //free memory
        freeGraph(graph, numNodes);
        freeGraph(colouredGraph, numNodes);
        freeGraph(benchmarkMinimumGraph, numNodes);
    }

    return 0;
}

int printHelp() {
    FILE* help = fopen(HELP_FILE_NAME, "r");

    char buffer[100];

    while(!feof(help)) {
        fgets(buffer, 1000, help);
        printf("%s", buffer);
    }

    fclose(help);

    return 0;
}