# nonklib

Header-only implementations of various data structures for learning purposes.

## Basic usage

First, make sure to create and include in your build a .c file with the following contents:

```c
#define NL_IMPLEMENTATION
#include "nl.h"
```

Otherwise, you won't have any definitions for the functions declared inside the header.

Now you can use the library from any of your .c files:

```c
#include <stdio.h>

#include "nl.h"

int main(int argc, char* argv[]) {
    nlVec my_vec = nlVecOf(int);

    int element = 69;
    nlVec_Push(&my_vec, element);
    nlVec_PushConst(&my_vec, int, 42);

    printf("length = %u; should = 2\n", my_vec.length);

    nlVec_Free(&my_vec);

    return 0;
}
```

## Goodies

Tests and benchmarks are bundled into the repository. Build then with CMake, e.g.:

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

Run the tests and the benchmarks respectively with:

```bash
./build/tests
./build/benchmarks
# You can run just a specific benchmark too:
./build/benchmarks millionaire
```

## Advanced usage

1. Define `nlMalloc` and `nlFree` in the implementation source file if you use an external memory allocator. See [the custom heap example](examples/custom_heap.c).
2. Use `#define NL_NO_DEFAULTS` to fine-tune what features you wish to include.
