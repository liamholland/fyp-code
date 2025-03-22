#include <stdio.h>
#include "testReferences.h"

int main(int argc, char const *argv[]) {
    
    //run tests
    for(int t = 0; t < NUM_TESTS; t++) {
        if(tests[t].test()) {
            printf("\033[38;5;196mFAILED\033[0m %s\n", tests[t].testName);
            return 1;
        }

        printf("\033[38;5;76mPASSED\033[0m %s\n", tests[t].testName);
    }

    return 0;
}
