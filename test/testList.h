#ifndef TEST_REF
#define TEST_REF

#include "testUtil.h"
#include "testTests.h"

#define REGISTER_TEST(t) { &t, #t }

typedef struct testStruct {
    int (*test)();
    const char* testName;
} test;

const test tests[] = {
    //test tests
    REGISTER_TEST(testPass),
    REGISTER_TEST(testFail),

    //test utils
    REGISTER_TEST(testInitialiseGraphNoNeighbours),
    REGISTER_TEST(testInitialiseGraphWithNeighbours),
    REGISTER_TEST(testCopyUnmodifiedGraph),
    REGISTER_TEST(testCopyModifiedGraph),
    REGISTER_TEST(testFreeGraph),
    REGISTER_TEST(testFindNumColoursUsed),
    REGISTER_TEST(testCountNumConflictsAll),
    REGISTER_TEST(testCountNumConflictsNone),
    REGISTER_TEST(testNumUncolouredNodes),
    REGISTER_TEST(testFetchNodes),
    REGISTER_TEST(testFetchNodesMoreThanGraph),
    REGISTER_TEST(testNodeInConflict),
    REGISTER_TEST(testWhichColoursInGraphOnlyOne),
    REGISTER_TEST(testWhichColoursInGraphAll),
    REGISTER_TEST(testFindConflictingNeighbours),
    REGISTER_TEST(testFindConflictingNeighboursNoConflicts),
    REGISTER_TEST(testCountNumberOfConflictsForNode),
    REGISTER_TEST(testFindConflictingNodesInGraph)
};

const int NUM_TESTS = sizeof(tests) / sizeof(test);

#endif