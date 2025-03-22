#ifndef TEST_REF
#define TEST_REF

#include "testUtil.h"
#include "testTests.h"

# define NUM_TESTS 7

typedef struct testStruct {
    int (*test)();
    const char* testName;
} test;

test tests[] = {
    //test tests
    {&testPass, "testPass"},
    {&testFail, "testFail"},

    //test utils
    {&testInitialiseGraphNoNeighbours, "testInitialiseGraphNoNeighbours"},
    {&testInitialiseGraphWithNeighbours, "testInitialiseGraphWithNeighbours"},
    {&testCopyUnmodifiedGraph, "testCopyUnmodifiedGraph"},
    {&testCopyModifiedGraph, "testCopyModifiedGraph"},
    {&testFindNumColoursUsed, "testFindNumColoursUsed"}
};

#endif