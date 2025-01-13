#include <stdio.h>
#include <math.h>
#include <string.h>
#include "visualisation.h"

//TODO: add colours to nodes

int traverseGraph(node** graph, int numNodes, node* focusNode) {
    switch (focusNode->degree)
    {
    case 0:
        printf("%d o", focusNode->id);
        break;
    case 1:
        printf("%d o---o %d\n", focusNode->id, focusNode->neighbours[0]->id);
        break;
    case 2:
        printNodeTwo(focusNode, focusNode->neighbours[0], focusNode->neighbours[1]);
        break;
    default:
        printNodeThreeOrMore(focusNode, focusNode->neighbours[0], focusNode->neighbours[1], focusNode->neighbours[focusNode->degree - 1]);
        int input = parseVisualisationCommand();
        if(input >= 0 && input < numNodes) {
            traverseGraph(graph, numNodes, graph[input]);
        }
        break;
    }

    return 0;
}

//CONSIDER: better encoding format for returns?
int parseVisualisationCommand() {
    char buffer[64];
    scanf_s("%s", buffer, sizeof(buffer));

    if(buffer[0] == 'e') {
        return -1;  //exit
    }
    else if(buffer[0] == 'j') {
        char jmpNode[64];   //jump
        strncpy(jmpNode, buffer + 1, strlen(buffer) - 1);
        return atoi(jmpNode);
    }
    else {
        printf("INVALID INPUT\n");
        return -2;
    }
}

int printBlankMargin(int width) {
    for(int i = 0; i < width + 1; i++) {
        printf(" ");
    }

    return 0;
}

//TODO: incorporate this into main function
int printNodeOrphan(node* main) {
    printf("%d o", main->id);

    return 0;
}

//TODO: incorporate this into main function
int printNodeOne(node* main, node* other) {
    printf("%d o---o %d\n", main->id, other->id);

    return 0;
}

int printNodeTwo(node* main, node* first, node* second) {
    //check number of characters in node id
    int numNodeDigits = main->id > 0 ? floor(log10(main->id)) : 1;

    printBlankMargin(numNodeDigits);
    printf("   /--o %d\n", first->id);
    printf("%d o\n", main->id);
    printBlankMargin(numNodeDigits);
    printf("   \\--o %d\n", second->id);

    return 0;
}

int printNodeThreeOrMore(node* main, node* first, node* middle, node* last) {
    //check number of characters in node id
    int numNodeDigits = main->id > 0 ? floor(log10(main->id)) : 1;
    
    //first connection
    if(middle->id - first->id > 1) {
        printBlankMargin(numNodeDigits);
        printf("   /--o %d\n", first->id);
        printBlankMargin(numNodeDigits);
        printf("  /   .\n");
        printBlankMargin(numNodeDigits);
        printf(" /    .\n");
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" /----o %d\n", first->id);
    }

    //middle connection
    printf("%d o-----o %d\n", main->id, middle->id);

    //last connection
    if(last->id - middle->id > 1) {
        printBlankMargin(numNodeDigits);
        printf(" \\    .\n");
        printBlankMargin(numNodeDigits);
        printf("  \\   .\n");
        printBlankMargin(numNodeDigits);
        printf("   \\--o %d\n", last->id);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" \\----o %d\n", last->id);
    }

    return 0;
}