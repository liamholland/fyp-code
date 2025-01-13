#include <stdio.h>
#include <math.h>
#include <string.h>
#include "visualisation.h"
#include "node.h"

int printGraph(node** graph, int numNodes) {
    switch (numNodes)
    {
    case 0:
        printf("ERROR: no nodes in graph\n");
        return 1;
    case 1:
        printNodeOrphan(graph[0]);
        break;
    case 2:
        printNodeOne(graph[0], graph[1]);
        break;
    case 3:
        printNodeTwo(graph[0], graph[1], graph[2]);
        break;
    case 4:
        printNodeThreeOrMore(graph[0], graph[1], graph[2], graph[3]);
        break;
    default:
        printNodeThreeOrMore(graph[0], graph[1], graph[2], graph[numNodes - 1]);
        int input = parseVisualisationCommand();
        if(input >= 0) {
            printGraph(graph, numNodes);
        }
        break;
    }
}

int parseVisualisationCommand() {
    char buffer[64];
    scanf_s("%s", buffer, sizeof(buffer));

    if(buffer[0] == "e") {
        return -1;
    }
    else if(buffer[0] == "j") {
        char jmpNode[64];
        strncpy(jmpNode, buffer + 1, strlen(buffer));
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

int printNodeOrphan(node* main) {
    printf("%d o", main->id);

    return 0;
}

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
        printf(" /    .\n");
        printBlankMargin(numNodeDigits);
        printf("  /   .\n");

        printBlankMargin(numNodeDigits);
        printf("   /--o %d", first->id);
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
        printf("   \\--o %d", last->id);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" \\----o %d\n", last->id);
    }

    return 0;
}