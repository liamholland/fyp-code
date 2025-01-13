#include <stdio.h>
#include <math.h>
#include <string.h>
#include "visualisation.h"

//TODO: add colours to nodes

int traverseGraph(node** graph, int numNodes, node* focusNode, int nextNeighbour) {
    switch (focusNode->degree)
    {
    case 0:
        printf("%d o\n", focusNode->id);
        break;
    case 1:
        printf("%d o---o %d\n", focusNode->id, focusNode->neighbours[0]->id);
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
        traverseGraph(graph, numNodes, focusNode, nextNeighbour + 1);
    }

    return 0;
}

//CONSIDER: better encoding format for returns?
int parseVisualisationCommand() {
    char buffer[64];
    scanf_s("%s", buffer, sizeof(buffer));

    if(buffer[0] == 'e') {
        return 0;  //exit
    }
    else if(buffer[0] == 'j') {
        char jmpNode[64];   //jump
        strncpy(jmpNode, buffer + 1, strlen(buffer) - 1);
        int target = atoi(jmpNode);
        int encodedTarget = 0 - target - 1;
        return encodedTarget;
    }
    else if(buffer[0] == 'n') {
        return 2;   //go to next node
    }
    else {
        printf("INVALID INPUT\n");
        return 1;
    }
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
    printf(" /--o %d\n", focusNode->neighbours[0]->id);
    printf("%d o\n", focusNode->id);
    printBlankMargin(numNodeDigits);
    printf(" \\--o %d\n", focusNode->neighbours[1]->id);

    return 0;
}

int printNodeThreeOrMore(node* focusNode, int middle) {
    //check number of characters in node id
    int numNodeDigits = focusNode->id > 0 ? floor(log10(focusNode->id)) : 1;
    
    //first connection
    if(middle > 1) {
        printBlankMargin(numNodeDigits);
        printf("   /--o %d\n", focusNode->neighbours[0]->id);
        printBlankMargin(numNodeDigits);
        printf("  /   .\n");
        printBlankMargin(numNodeDigits);
        printf(" /    .\n");
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" /----o %d\n", focusNode->neighbours[0]->id);
    }

    //middle connection
    printf("%d o-----o %d\n", focusNode->id, focusNode->neighbours[middle]->id);

    //last connection
    if(middle < focusNode->degree - 2) {
        printBlankMargin(numNodeDigits);
        printf(" \\    .\n");
        printBlankMargin(numNodeDigits);
        printf("  \\   .\n");
        printBlankMargin(numNodeDigits);
        printf("   \\--o %d\n", focusNode->neighbours[focusNode->degree - 1]->id);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" \\----o %d\n", focusNode->neighbours[focusNode->degree - 1]->id);
    }

    return 0;
}