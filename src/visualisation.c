#include <stdio.h>
#include <math.h>
#include <string.h>
#include "visualisation.h"

int traverseGraph(node** graph, int numNodes, node* focusNode, int nextNeighbour) {
    printf("--- node %d ---\ndegree: %d; colour: %d\n\n", focusNode->id, focusNode->degree, focusNode->colour);

    switch (focusNode->degree)
    {
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

    int input = parseVisualisationCommand();
    if(input < 0) {
        printf("\e[1;1H\e[2J"); //clear the screen
        int targetNode = (input * -1) - 1;
        traverseGraph(graph, numNodes, graph[targetNode], 1);
    }
    else if(input == 1) {
        printf("ERROR OCCURRED\n");
    }
    else if(input == 2) {
        printf("\e[1;1H\e[2J"); //clear the screen
        if(nextNeighbour + 1 == focusNode->degree - 1) {
            //focus on the last neighbour if there are no more to display
            traverseGraph(graph, numNodes, focusNode->neighbours[focusNode->degree - 1], 1);
        }
        else {
            traverseGraph(graph, numNodes, focusNode, nextNeighbour + 1);
        }
    }

    return 0;
}

int parseVisualisationCommand() {
    char buffer[64];
    printf(">> ");
    scanf("%s", buffer);

    if(buffer[0] == 'e') {
        return 0;  //exit
    }
    else if(buffer[0] == 'j') {
        char jmpNode[64];
        strncpy(jmpNode, buffer + 1, strlen(buffer) - 1);   //get a string slice
        int target = atoi(jmpNode);
        int encodedTarget = 0 - target - 1;
        return encodedTarget;   //jump to this node
    }
    else if(buffer[0] == 'n') {
        return 2;   //display next neighbour
    }
    else {
        printf("INVALID INPUT\n");
        return 1;
    }
}

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