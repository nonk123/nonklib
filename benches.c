#include "bench_runner.c"

Bench(millionaire) {
    nlVec vec = nlVecOf(size_t);

    for (size_t i = 1; i <= 1000000; i++) {
        nlVec_Push(&vec, i);
    }

    nlVec_Free(&vec);
}

Bench(multimillionaire) {
    nlVec vec = nlVecOf(int);
    int sequence[] = {69, 420, 777};

    for (size_t i = 1; i <= 10000000; i++) {
        nlVec_Push(&vec, sequence[i % 3]);
    }

    nlVec_Free(&vec);
}

struct Bench benches[] = {
    millionaire,
    multimillionaire,
    Bench_NULL,
};
