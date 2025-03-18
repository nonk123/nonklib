#include <stdio.h>
#include <stdlib.h>

unsigned int tests_run = 0, tests_failed = 0;

typedef void (*TestFn)();
TestFn tests[];

int main(int argc, char* argv[]) {
    TestFn* ptr = tests;

    while (*ptr != NULL) {
        (*ptr++)();
    }

    printf("Success rate: %u/%u\n", tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int __test_failure;

int __run_test(const char* name, void (*test)()) {
    tests_run++;

    __test_failure = 0;
    test();

    if (__test_failure) {
        printf("Test '%s' failed\n", name);
        tests_failed++;
    } else {
        printf("Test '%s' passed\n", name);
    }
}

#define Assert(expr)                                                                                                   \
    if (!(expr)) {                                                                                                     \
        printf("Assertion failed: %s\n", #expr);                                                                       \
        __test_failure = 1;                                                                                            \
        return;                                                                                                        \
    }

#define Test(name)                                                                                                     \
    void test_##name##__body();                                                                                        \
                                                                                                                       \
    void name() {                                                                                                      \
        __run_test(#name, test_##name##__body);                                                                        \
    }                                                                                                                  \
                                                                                                                       \
    void test_##name##__body()

#define NL_IMPLEMENTATION
#include "nl.h"
