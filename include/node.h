#ifndef NODE
#define NODE

/*
a node has a colour, id (postion in array), degree and an array of neighbour nodes

the id was included mainly to make copying easier

nodes are commonly used in the context of a node**. this is an array of node pointers.
this data structure has a number of benefits when we are constantly accessing nodes in the same graph.
i do not encapsulate the node** in a struct such as `nodeArray` as that would increase the complexity of all
of the related code. Iterating over a graph looks like this:

```C
int iterateOverGraph(node** graph, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        graph[n]->whatever;
    }
    return 0;
}
```

instead of adding an extra step which will either add an extra access operation, or make the code
harder to read:

```C
int iterateOverGraph(nodeArray graph, int numNodes) {
    for(int n = 0; n < numNodes; n++) {
        nodeArray->data[n]->whatever;
    }
    return 0;
}
```

in the end, this program is a research project written in C, not C++; pointers are going to be used extensively.
i believe obscuring the places where they are used would make the code considerably worse in this case.

the other major benefit of the `node` is that subgraphs (like the node's neighbours) can assessed using all of the
exact same utility functions as the whole graph, since they are also simply arrays of node pointers

parameter names are clear on what the pointers are doing throughout the program
*/

typedef struct nodeStruct {
    int id;
    int colour;
    int degree;
    struct nodeStruct** neighbours;
} node;

#endif