#include <stdio.h>

#define NL_IMPLEMENTATION
#include "nl.h"

static unsigned int tests_run = 0, tests_failed = 0;
static void run_tests(void);

int main(int argc, char* argv[]) {
    run_tests();
    printf("Success rate: %u/%u\n", tests_run - tests_failed, tests_run);
    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

#define Assert(expr)                                                                               \
    if (!(expr)) {                                                                                 \
        printf("Assertion failed: %s\n", #expr);                                                   \
        test__failure = 1;                                                                         \
        return;                                                                                    \
    }

static int test__failure;

static int test__run(const char* name, void (*test)(void)) {
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
        test__run(#name, test_##name##__body);                                                     \
    }                                                                                              \
                                                                                                   \
    void test_##name##__body(void)

Test(vec_empty) {
    NL_Vec vec = NL_VecOf(int);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));

    NL_Vec_Free(&vec);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));
}

Test(vec_push) {
    NL_Vec vec = NL_VecOf(int);

    int value = 42;
    NL_Vec_Push(&vec, value);

    Assert(vec.data != NULL);
    Assert(vec.length == 1);
    Assert(vec.capacity == NL_Vec_BASE_CAPACITY);
    Assert(vec.element_size == sizeof(int));
    Assert(vec.data[0 * vec.element_size] == value);

    NL_Vec_Free(&vec);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));
}

Test(vec_push_const) {
    NL_Vec vec = NL_VecOf(int);
    NL_Vec_PushConst(&vec, int, 42);
    NL_Vec_PushConst(&vec, int, 69);
    NL_Vec_PushConst(&vec, int, 777);

    Assert(vec.length == 3);
    Assert(vec.capacity == NL_Vec_BASE_CAPACITY);
    Assert(vec.element_size == sizeof(int));

    int* data = (int*)vec.data;
    Assert(data[0] == 42);
    Assert(data[1] == 69);
    Assert(data[2] == 777);

    NL_Vec_Free(&vec);
}

static void run_tests(void) {
    test_vec_empty();
    test_vec_push();
    test_vec_push_const();
}
