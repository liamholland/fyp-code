#ifndef NODE
#define NODE

// a node has a colour, id (postion in array), degree and an array of neighbour nodes
typedef struct nodeStruct {
    int id;     // i included this to make copying easier
    int colour;
    int degree;
    struct nodeStruct** neighbours;
} node;

#endif