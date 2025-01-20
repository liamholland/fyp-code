#include <stdio.h>
#include <math.h>
#include <string.h>
#include "visualisation.h"

//TODO: add colours to nodes

int traverseGraph(node** graph, int numNodes, node* focusNode, int nextNeighbour) {
    printf("--- node %d ---\ndegree: %d; colour: %d\n\n", focusNode->id, focusNode->degree, focusNode->colour);

    switch (focusNode->degree) {
        case 0:
            printf("%d \e[38;5;%dmo\e[0m\n", focusNode->id, normaliseColour(focusNode->colour));
            break;
        case 1:
            printf("%d \e[38;5;%dmo\e[0m---\e[38;5;%dmo\e[0m %d\n", 
                focusNode->id, 
                normaliseColour(focusNode->colour), 
                normaliseColour(focusNode->neighbours[0]->colour),
                focusNode->neighbours[0]->id
            );
            break;
        case 2:
            printNodeTwo(focusNode);
            break;
        default:
            printNodeThreeOrMore(focusNode, nextNeighbour);
            break;
    }

    char buffer[8];
    printf(">> ");
    scanf("%s", buffer);

    //parse command
    switch (buffer[0]) {
        case 'e':
            return 0;
        case 'j':
            printf("\e[1;1H\e[2J"); //clear the screen
            return traverseGraph(graph, numNodes, graph[atoi(buffer + 1)], 1);
        case 'n':
            printf("\e[1;1H\e[2J"); //clear the screen

            if(nextNeighbour + 1 == focusNode->degree - 1) {
                //focus on the last neighbour if there are no more to display
                return traverseGraph(graph, numNodes, focusNode->neighbours[focusNode->degree - 1], 1);
            }
            else {
                return traverseGraph(graph, numNodes, focusNode, nextNeighbour + 1);
            }
        case 'p':
            printf("\e[1;1H\e[2J"); //clear the screen

            if(nextNeighbour - 1 == 0) {
                //focus on the last neighbour if there are no more to display
                return traverseGraph(graph, numNodes, focusNode->neighbours[0], 1);
            }
            else {
                return traverseGraph(graph, numNodes, focusNode, nextNeighbour - 1);
            }
        case 'r':
            return -1;
        default:
            printf("INVALID INPUT\n");
            return 1;
    }
}

//normalised relative to the terminal ANSI 8-bit colours
//https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
int normaliseColour(int colour) {
    int terminalColour = (colour % 215) + 16;
    return terminalColour;
}

int printBlankMargin(int width) {
    for(int i = 0; i < width + 1; i++) {
        printf(" ");
    }

    return 0;
}

int printTraversalModeCommands() {
    printf("\n----------\ntraversal mode\n----------\n");
    printf("COMMANDS:\n");
    printf("\
        n: display next neighbour\n\
        p: display previous neighbour\n\
        j[number]: jump to node (e.g. j5)\n\
        r: rerun the program on the coloured graph\n\
        e: exit program\n\
        \n");
    return 0;
}

int printNodeTwo(node* focusNode) {
    //check number of characters in node id
    int numNodeDigits = focusNode->id > 0 ? floor(log10(focusNode->id)) : 1;

    printBlankMargin(numNodeDigits);
    printf(" /--\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[0]->colour), focusNode->neighbours[0]->id);
    printf("%d \e[38;5;%dmo\e[0m\n", focusNode->id, normaliseColour(focusNode->colour));
    printBlankMargin(numNodeDigits);
    printf(" \\--\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[1]->colour), focusNode->neighbours[1]->id);

    return 0;
}

int printNodeThreeOrMore(node* focusNode, int middle) {
    //check number of characters in node id
    int numNodeDigits = focusNode->id > 0 ? floor(log10(focusNode->id)) : 1;
    
    //first connection
    if(middle > 1) {
        printBlankMargin(numNodeDigits);
        printf("   /--\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[0]->colour) ,focusNode->neighbours[0]->id);
        printBlankMargin(numNodeDigits);
        printf("  /   .\n");
        printBlankMargin(numNodeDigits);
        printf(" /    .\n");
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" /----\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[0]->colour), focusNode->neighbours[0]->id);
    }

    //middle connection
    printf("%d \e[38;5;%dmo\e[0m-----\e[38;5;%dmo\e[0m %d\n", 
        focusNode->id, 
        normaliseColour(focusNode->colour), 
        normaliseColour(focusNode->neighbours[middle]->colour), 
        focusNode->neighbours[middle]->id
    );

    //last connection
    if(middle < focusNode->degree - 2) {
        printBlankMargin(numNodeDigits);
        printf(" \\    .\n");
        printBlankMargin(numNodeDigits);
        printf("  \\   .\n");
        printBlankMargin(numNodeDigits);
        printf("   \\--\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[focusNode->degree - 1]->colour), focusNode->neighbours[focusNode->degree - 1]->id);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" \\----\e[38;5;%dmo\e[0m %d\n", normaliseColour(focusNode->neighbours[focusNode->degree - 1]->colour), focusNode->neighbours[focusNode->degree - 1]->id);
    }

    return 0;
}