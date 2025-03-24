#ifndef TEST_UTIL
#define TEST_UTIL

int testInitialiseGraphNoNeighbours();
int testInitialiseGraphWithNeighbours();

int testCopyUnmodifiedGraph();
int testCopyModifiedGraph();

int testFreeGraph();

int testFindNumColoursUsed();

int testCountNumConflictsAll();
int testCountNumConflictsNone();

int testNumUncolouredNodes();

int testFetchNodes();
int testFetchNodesMoreThanGraph();

int testNodeInConflict();

int testWhichColoursInGraphOnlyOne();
int testWhichColoursInGraphAll();

int testFindConflictingNodesInGraph();

int testFindConflictingNeighbours();
int testFindConflictingNeighboursNoConflicts();

int testCountNumberOfConflictsForNode();

int testRemoveEdge();

int testMakeNodeOrphan();

int testRemoveNode();

int testAddEdge();

int testFindHighestDegree();

int testFindLowestDegree();

int testRemoveNodePointerFromList();

#endif