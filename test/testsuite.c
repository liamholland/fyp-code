#include <stdio.h>

int pass();
int fail();
int addTest(int (*)());

int (*testFunctions[1000]) ();
int numTests = 0;

int main(int argc, char const *argv[]) {
    return 0;
}

int pass() {
    printf("\e[38;5;10mPASSED\e[0m\n");
    return 0;
}

int fail() {
    printf("\e[38;5;9mFAILED\e[0m\n");
    return 1;
}

int addTest(int (*testFunction) ()) {
    testFunctions[numTests++] = testFunction;
    return 0;
}