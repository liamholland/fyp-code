#include <stdlib.h>
#include "graphutil.h"
#include "movementKernels.h"

node* randomMoveKernel(node* agent, int numMoves) {
    for(int m = 0; m < numMoves; m++) {
        agent = agent->neighbours[rand() % agent->degree];
    }

    return agent;
}

node* optimalMoveKernel(node* agent, int numMoves) {
    for(int m = 0; m < numMoves; m++) {
        if(agent->degree == 0) {
            break;  //cant move the agent; on an orphan node
        }
        else if(findNumUncolouredNodes(agent->neighbours, agent->degree) > 0) {
            for(int nb = 0; nb < agent->degree; nb++) {
                if(!agent->neighbours[nb]->colour) {
                    agent = agent->neighbours[nb];
                }
            }
        }
        else {
            node* maxColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour > maxColourNode->colour) {
                    maxColourNode = agent->neighbours[nb];
                }
            }

            agent = maxColourNode;
        }
    }

    return agent;
}

/*
need to find some way to include the bad actor in this

node* badActorMoveKernel(node* agent, int numMoves) {
    for(int m = 0; m < numMoves; m++) {
        if(agent->degree == 0) {
            break;  //cant move the agent; on an orphan node
        }
        else if(findNumUncolouredNodes(agent->neighbours, agent->degree) > 0) {
            for(int nb = 0; nb < agent->degree; nb++) {
                if(!agent->neighbours[nb]->colour) {
                    agent = agent->neighbours[nb];

                    if(agent == badActor) {
                        badActor = agent;
                    }

                    break;
                }
            }
        }
        else if(agent == badActor) {
            node* minColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour < minColourNode->colour) {
                    minColourNode = agent->neighbours[nb];
                }
            }

            agent = minColourNode;
            badActor = agent;
        }
        else {
            node* maxColourNode = agent->neighbours[0];
            for(int nb = 0; nb < agent->degree; nb++) {
                if(agent->neighbours[nb]->colour > maxColourNode->colour) {
                    maxColourNode = agent->neighbours[nb];
                }
            }

            agent = maxColourNode;
        }
    }

    return agent;
}

*/
