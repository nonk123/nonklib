#include <stdio.h>

void* static_malloc(size_t);
void static_free(void*);

#define NL_IMPLEMENTATION
#define nlMalloc static_malloc
#define nlFree static_free
#include "nl.h"

#define TOTAL_MEM (4096)
nlByte heap_start[TOTAL_MEM], *heap_mem = heap_start, *heap_end = heap_start + TOTAL_MEM;

void* static_malloc(size_t size) {
    if (heap_mem + size >= heap_end) {
        printf("Out of memory!!!\n");
        return NULL;
    }

    nlByte* ptr = heap_mem;
    heap_mem += size;
    return ptr;
}

void static_free(void* ptr) {
    nlByte* heap_ptr = (nlByte*)ptr;

    if (heap_ptr < heap_start || heap_ptr >= heap_end) {
        printf("Invalid free!!!\n");
    }
}

int main(int argc, char* argv[]) {
    nlVec vec = nlVecOf(int);
    size_t full_heap = TOTAL_MEM / nlVec_GROWTH_FACTOR / sizeof(int);

    for (int i = 1; i <= full_heap; i++) {
        nlVec_Push(&vec, i);
    }

    int mid = ((int*)vec.data)[vec.length / 2];
    printf("The middle element is %d\n", mid);

    nlVec_Free(&vec);

    return 0;
}
