#include "stdio.h"
#include "math.h"
#include "node.h"

//private helper function
int printBlankMargin(int width) {
    for(int i = 0; i < width + 1; i++) {
        printf(" ");
    }

    return 0;
}

int printNode(int node, int start, int middle, int end) {
    //check number of characters in node id
    int numNodeDigits = node > 0 ? floor(log10(node)) : 1;
    
    //first connection
    if(middle - start > 1) {
        printBlankMargin(numNodeDigits);
        printf(" /    .\n");
        printBlankMargin(numNodeDigits);
        printf("  /   .\n");

        printBlankMargin(numNodeDigits);
        printf("   /--o %d", end);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" /----o %d\n", start);
    }

    //middle connection
    printf("%d o-----o %d\n", node, middle);

    //last connection
    if(end - middle > 1) {
        printBlankMargin(numNodeDigits);
        printf(" \\    .\n");
        printBlankMargin(numNodeDigits);
        printf("  \\   .\n");

        printBlankMargin(numNodeDigits);
        printf("   \\--o %d", end);
    }
    else {
        printBlankMargin(numNodeDigits);
        printf(" \\----o %d\n", end);
    }


    return 0;
}