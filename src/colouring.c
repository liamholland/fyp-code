#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "graphgenerator.h"
#include "graphcolourer.h"
#include "centralisedgraphcolouring.h"
#include "graphutil.h"
#include "visualisation.h"
#include "dynamicKernels.h"
#include "colouringKernels.h"
#include "saving.h"

#define HELP_FILE_NAME "help.txt"

int printHelp();

int main(int argc, char const *argv[]) {
    srand((unsigned) time(NULL));

    int numNodes = 10;
    char generator = 'r';
    int visualise = 0;
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

    //kernels
    char cKernelCode = 'm';
    char dKernelCode = 'x';

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
        else if(!strcmp(argv[i], "-p")) {
            prob = atof(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-k")) {
            cKernelCode = *argv[i + 1];
        }
        else if(!strcmp(argv[i], "-c")) {
            minColour = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-M")) {
            maxIterations = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-S")) {
            save = 1;
        }
        else if(!strcmp(argv[i], "-A")) {
            autoRuns = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-d")) {
            dKernelCode = *argv[i + 1];  
        }
        else if(!strcmp(argv[i], "-C")) {
            maxColour = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-a")) {
            numAgents = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-m")) {
            numMoves = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-v")) {
            visualise = 1;
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

    //set colouring kernel
    int (*agentController) (node**, int, int);
    switch (cKernelCode) {
        case 'r':
            agentController = &randomKernel;
            break;
        case 'd':
            agentController = &colourblindFishAgentDecrement;
            break;
        case 'i':
            agentController = &colourblindFishAgentIncrement;
            break;
        case 'a':
            agentController = &amongUsKernel;
            break;
        case 'm':
            agentController = &minimumAgent;
            break;
        default:
            printf("invalid colouring kernel\n");
            return 1;
    }

    //set the dynamic kernel
    int (*dynamicKernel) (node***, int*, node*, node***, int*);
    switch (dKernelCode) {
        case 'e':
            dynamicKernel = &possiblyRemoveEdgeKernel;
            break;
        case 'n':
            dynamicKernel = &possiblyRemoveNodeKernel;
            break;
        case 'o':
            dynamicKernel = &removeOrphanNodesKernel;
            break;
        case 'x':
            dynamicKernel = NULL;
            break;
        default:
            printf("invalid dynamic kernel\n");
            return 1;
    }

    //graph variables
    node** graph;
    node** colouredGraph;
    node** benchmarkMinimumGraph;

    if(save) {
        char description[100];
        snprintf(description, 100, "generator: %c; coloring kernel: %c; dynamic kernel: %c; no. nodes: %d; probability: %.3f;",
            generator, cKernelCode, dKernelCode, numNodes, prob);
        addHeadersToResultsFile(description);
    }

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

        colouredGraph = agentColour(graph, &numNodes, maxIterations, numAgents, numMoves, minColour, maxColour + 1, agentController, dynamicKernel, save);

        if(visualise) {
            autoRuns = 1;   //should only run once if viewing the graph

            //find the highest degree node
            node* highestDegreeNode = findNodeWithHighestDegree(colouredGraph, numNodes);

            //enter interactive traversal mode
            printTraversalModeCommands();
            while(traverseGraph(colouredGraph, numNodes, highestDegreeNode, 1) < 0) {
                //run it again
                colouredGraph = agentColour(colouredGraph, &numNodes, maxIterations, numAgents, numMoves, minColour, maxColour + 1, agentController, dynamicKernel, save);
            }
        }

        //free memory
        freeGraph(graph, numNodes);
        freeGraph(colouredGraph, numNodes);
        freeGraph(benchmarkMinimumGraph, numNodes);
    }

    if(save) {
        addBufferColumnToConflictsFile(2);
        addBufferRowToResultsFile(2);
    }

    return 0;
}

int printHelp() {
    FILE* help = fopen(HELP_FILE_NAME, "r");

    char buffer[100];

    while(!feof(help)) {
        fgets(buffer, 100, help);
        printf("%s", buffer);
    }

    fclose(help);

    return 0;
}