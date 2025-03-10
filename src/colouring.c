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
#include "movementKernels.h"
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
    char mKernelCode = 'x';
    const char* kernelConfig;

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

            //if name file name is provided, set it
            if(i + 1 < argc && !(*argv[i + 1] == '-') && setFileNamePrepend(argv[i + 1])) {
                return 1;   //do not want to accidentally overwrite saved data
            }
        }
        else if(!strcmp(argv[i], "-A")) {
            autoRuns = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-d")) {
            dKernelCode = *argv[i + 1];  
        }
        else if(!strcmp(argv[i], "-K")) {
            kernelConfig = argv[i + 1];
            int configLength = strlen(kernelConfig);
            if(configLength < 3 || configLength > 3) {
                printf("invalid kernel config\n");
                return 1;
            }
        }
        else if(!strcmp(argv[i], "-C")) {
            maxColour = atoi(argv[i + 1]) - 1;
        }
        else if(!strcmp(argv[i], "-a")) {
            numAgents = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-m")) {
            numMoves = atoi(argv[i + 1]);
        }
        else if(!strcmp(argv[i], "-w")) {
            mKernelCode = *argv[i + 1];
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

    //set kernel config
    if(kernelConfig != NULL) {
        cKernelCode = kernelConfig[0];
        dKernelCode = kernelConfig[1];
        mKernelCode = kernelConfig[2];
    }

    //set colouring kernel
    int (*colouringKernel) (node*, int);
    switch (cKernelCode) {
        case 'r':
            colouringKernel = &randomKernel;
            break;
        case 'd':
            colouringKernel = &colourblindAgentDecrement;
            break;
        case 'i':
            colouringKernel = &colourblindAgentIncrement;
            break;
        case 'a':
            colouringKernel = &amongUsKernel;
            break;
        case 'm':
            colouringKernel = &minimumAgent;
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

    //set the movement kernel
    node* (*movementKernel) (node*, int);
    switch(mKernelCode) {
        case 'r':
            movementKernel = &randomMoveKernel;
            break;
        case 'o':
            movementKernel = &optimalMoveKernel;
            break;
        case 'x':
            movementKernel = NULL;
            break;
        default:
            printf("invalid movement kernel\n");
            return 1;
    }

    //graph variables
    node** graph;
    node** colouredGraph;
    node** benchmarkMinimumGraph;

    if(save) {
        char description[100];
        snprintf(description, 100, "generator: %c; coloring kernel: %c; dynamic kernel: %c; movement kernel: %c; no. nodes: %d; probability: %.3f;",
            generator, cKernelCode, dKernelCode, mKernelCode, numNodes, prob);
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

        printf("highest degree: %d\n", findNodeWithHighestDegree(graph, numNodes)->degree);
        printf("lowest degree: %d\n", findNodeWithLowestDegree(graph, numNodes)->degree);

        //colour the graph
        benchmarkMinimumGraph = minimumColour(graph, numNodes);
        
        if(useBenchmark) {
            maxColour = findNumColoursUsed(benchmarkMinimumGraph, numNodes, numNodes + 1);
        }

        colouredGraph = agentColour(graph, &numNodes, maxIterations, &numAgents, numMoves, minColour, maxColour + 1, save, colouringKernel, dynamicKernel, movementKernel);

        // colouredGraph = pathColour(graph, numNodes, graph[0], graph[1], minColour, maxColour, save, colouringKernel);

        if(visualise) {
            autoRuns = 1;   //should only run once if viewing the graph

            //find the highest degree node
            node* highestDegreeNode = findNodeWithHighestDegree(colouredGraph, numNodes);

            //enter interactive traversal mode
            printTraversalModeCommands();
            while(traverseGraph(colouredGraph, numNodes, highestDegreeNode, 1) < 0) {
                //run it again
                colouredGraph = agentColour(colouredGraph, &numNodes, maxIterations, &numAgents, numMoves, minColour, maxColour + 1, save, colouringKernel, dynamicKernel, movementKernel);
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