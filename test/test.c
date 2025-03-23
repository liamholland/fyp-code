#include <stdio.h>
#include "testList.h"

int main(int argc, char const *argv[]) {

    //run tests
    for(int t = 0; t < NUM_TESTS; t++) {
        printf("TESTING %s... ", tests[t].testName);
        
        if(tests[t].test()) {
            printf("\033[38;5;196mFAILED\033[0m\n");    // :(
            return 1;
        }

        printf("\033[38;5;76mPASSED\033[0m\n");         // :)
    }

    printf("\033[38;5;76mALL TESTS PASSED\033[0m\n");

    return 0;
}
