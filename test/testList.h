#ifndef TEST_REF
#define TEST_REF

#include "testUtil.h"
#include "testTests.h"

typedef struct testStruct {
    int (*test)();
    const char* testName;
} test;

const test tests[] = {
    //test tests
    {&testPass, "testPass"},
    {&testFail, "testFail"},

    //test utils
    {&testInitialiseGraphNoNeighbours, "testInitialiseGraphNoNeighbours"},
    {&testInitialiseGraphWithNeighbours, "testInitialiseGraphWithNeighbours"},
    {&testCopyUnmodifiedGraph, "testCopyUnmodifiedGraph"},
    {&testCopyModifiedGraph, "testCopyModifiedGraph"},
    {&testFreeGraph, "testFreeGraph"},
    {&testFindNumColoursUsed, "testFindNumColoursUsed"},
    {&testCountNumConflictsAll, "testCountNumConflictsAll"},
    {&testCountNumConflictsNone, "testCountNumConflictsNone"},
    {&testNumUncolouredNodes, "testNumUncolouredNodes"},
    {&testFetchNodes, "testFetchNodes"},
    {&testFetchNodesMoreThanGraph, "testFetchNodesMoreThanGraph"},
    {&testNodeInConflict, "testNodeInConflict"}
};

const int NUM_TESTS = sizeof(tests) / sizeof(test);

#endif