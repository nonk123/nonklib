#include "test_runner.c"

Test(vec_empty) {
    nlVec vec = nlVecOf(int);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));

    nlVec_Free(&vec);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));
}

Test(vec_push) {
    nlVec vec = nlVecOf(int);

    int value = 42;
    nlVec_Push(&vec, value);

    Assert(vec.data != NULL);
    Assert(vec.length == 1);
    Assert(vec.capacity == nlVec_BASE_CAPACITY);
    Assert(vec.element_size == sizeof(int));
    Assert(((int*)vec.data)[0] == value);

    nlVec_Free(&vec);

    Assert(vec.data == NULL);
    Assert(vec.length == 0);
    Assert(vec.capacity == 0);
    Assert(vec.element_size == sizeof(int));
}

Test(vec_push_const) {
    nlVec vec = nlVecOf(int);
    nlVec_PushConst(&vec, int, 42);
    nlVec_PushConst(&vec, int, 69);
    nlVec_PushConst(&vec, int, 777);

    Assert(vec.length == 3);
    Assert(vec.capacity == nlVec_BASE_CAPACITY);
    Assert(vec.element_size == sizeof(int));

    int* data = (int*)vec.data;
    Assert(data[0] == 42);
    Assert(data[1] == 69);
    Assert(data[2] == 777);

    nlVec_Free(&vec);
}

TestFn tests[] = {
    vec_empty,
    vec_push,
    vec_push_const,
    NULL,
};
