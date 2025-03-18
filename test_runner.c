#include <stdio.h>

#define NL_IMPLEMENTATION
#include "nl.h"

typedef void (*TestFn)(void);

unsigned int tests_run = 0, tests_failed = 0;
TestFn tests[];

void run_tests() {
    TestFn* ptr = &tests[0];

    while (*ptr != NULL) {
        (*ptr++)();
    }
}

int main(int argc, char* argv[]) {
    run_tests();
    printf("Success rate: %u/%u\n", tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int test__failure;

#define Assert(expr)                                                                               \
    if (!(expr)) {                                                                                 \
        printf("Assertion failed: %s\n", #expr);                                                   \
        test__failure = 1;                                                                         \
        return;                                                                                    \
    }

int __run_test(const char* name, void (*test)(void)) {
    tests_run++;

    test__failure = 0;
    test();

    if (test__failure) {
        printf("Test '%s' failed\n", name);
        tests_failed++;
    } else {
        printf("Test '%s' passed\n", name);
    }
}

#define Test(name)                                                                                 \
    void test_##name##__body(void);                                                                \
                                                                                                   \
    void test_##name(void) {                                                                       \
        __run_test(#name, test_##name##__body);                                                    \
    }                                                                                              \
                                                                                                   \
    void test_##name##__body(void)
