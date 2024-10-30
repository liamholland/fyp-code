#include <stdio.h>
#include <time.h>
#include <string.h>
#include "graphgenerator.h"
#include "graphcolourer.h"
#include "node.h"
#include "graphutil.h"

int main(int argc, char const *argv[]) {

    int numNodes = 10;
    int maxIterations = 100;
    float prob = 0.5;
    int verbose = 0;
    char generator = 'o';

    for(int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-n")) {
            numNodes = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-m")) {
            maxIterations = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-v")) {
            verbose = 1;
        }
        else if(!strcmp(argv[i], "-p")) {
            prob = atof(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-g")) {
            generator = *argv[i + 1];
        }
    }

    //generate the graph
    node** graph;
    switch (generator) {
    case 'o':
        graph = generateRingGraph(numNodes);
        break;
    case 'r':
        graph = generateRandomGraph(numNodes, prob);
        break;    
    default:
        printf("invalid generator");
        return 1;
    }

    //colour the graph
    node** colouredGraph = imFeelingLuckyColour(graph, numNodes, maxIterations);

    if(verbose) {
        printGraph(colouredGraph, numNodes);
    }

    //free memory
    freeGraph(graph, numNodes);
    freeGraph(colouredGraph, numNodes);

    return 0;
}