#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Bench_NULL                                                                                                     \
    (struct Bench) {                                                                                                   \
        .name = NULL, .callback = NULL,                                                                                \
    }

struct Bench {
    const char* name;
    void (*callback)();
};

struct Bench benches[];
size_t heap_mem = 0;

void* counting_malloc(size_t size) {
    void* ptr = malloc(size);

    if (ptr != NULL) {
        heap_mem += size;
    }

    return ptr;
}

int run(const struct Bench* bench) {
    heap_mem = 0;

    clock_t tic = clock();
    bench->callback();
    clock_t toc = clock();

    double wasted_s = (double)(toc - tic) / CLOCKS_PER_SEC, wasted_ms = wasted_s * 1000.0;
    size_t wasted_kb = heap_mem / 1024, wasted_mb = wasted_kb / 1024;

    printf("Bench '%s' wasted %.1fms & %uKB ~ %uMB\n", bench->name, wasted_ms, wasted_kb, wasted_mb);
}

int main(int argc, char* argv[]) {
    struct Bench* ptr = benches;

    if (argc <= 1) {
        for (; ptr->name != NULL; ptr++) {
            run(ptr);
        }
    } else {
        for (; ptr->name != NULL; ptr++) {
            if (strcmp(ptr->name, argv[1]) == 0) {
                run(ptr);
            }
        }
    }

    return 0;
}

#define Bench(bName)                                                                                                   \
    void bench_##bName##__body();                                                                                      \
                                                                                                                       \
    const struct Bench bName = {                                                                                       \
        .name = #bName,                                                                                                \
        .callback = bench_##bName##__body,                                                                             \
    };                                                                                                                 \
                                                                                                                       \
    void bench_##bName##__body()

#define NL_IMPLEMENTATION
#define nlMalloc counting_malloc
#define nlFree free
#include "nl.h"
