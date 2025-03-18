# nonklib

Header-only implementations of various data structures for learning purposes.

## Usage

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
    NL_Vec my_vec = NL_VecOf(int);

    int element = 69;
    NL_Vec_Push(&my_vec, element);
    NL_Vec_PushConst(&my_vec, int, 42);

    printf("length = %u; should = 2\n", my_vec.length);

    return 0;
}
```
