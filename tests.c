#include "test_runner.c"

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
    Assert(((int*)vec.data)[0] == value);

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

TestFn tests[] = {
    test_vec_empty,
    test_vec_push,
    test_vec_push_const,
    NULL,
};
