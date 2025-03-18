#ifndef NL_H
#define NL_H

#include <stdlib.h>

#ifndef nlMalloc
#define nlMalloc malloc
#endif

#ifndef nlFree
#define nlFree free
#endif

typedef unsigned char nlByte;

typedef struct nlVec nlVec;
struct nlVec {
    nlByte* data;
    size_t length, capacity, element_size;
};

#define nlVecOf(T)                                                                                                     \
    (nlVec) {                                                                                                          \
        .data = NULL, .length = 0, .capacity = 0, .element_size = sizeof(T),                                           \
    }

void nlVec_Free(nlVec* vec)
#ifdef NL_IMPLEMENTATION
{
    if (vec->data != NULL) {
        nlFree(vec->data);
        vec->data = NULL;
        vec->length = 0;
        vec->capacity = 0;
    }
}
#else
    ;
#endif

#define nlVec_BASE_CAPACITY (512)
#define nlVec_GROWTH_FACTOR (2)

void nlVec_MaybeInit(nlVec* vec)
#ifdef NL_IMPLEMENTATION
{
    if (vec->data == NULL) {
        vec->data = nlMalloc(nlVec_BASE_CAPACITY * vec->element_size);
        vec->capacity = nlVec_BASE_CAPACITY;
    }
}
#else
    ;
#endif

void nlVec_MaybeGrow(nlVec* vec)
#ifdef NL_IMPLEMENTATION
{
    nlVec_MaybeInit(vec);

    if (vec->length < vec->capacity) {
        return;
    }

    nlByte* old_data = vec->data;
    vec->data = nlMalloc(vec->capacity * vec->element_size * nlVec_GROWTH_FACTOR);

    for (size_t i = 0; i < vec->capacity * vec->element_size; i++) {
        vec->data[i] = old_data[i];
    }

    vec->capacity *= nlVec_GROWTH_FACTOR;
    nlFree(old_data);
}
#else
    ;
#endif

void nlVec_PushGeneric(nlVec* vec, const nlByte* elt)
#ifdef NL_IMPLEMENTATION
{
    nlVec_MaybeGrow(vec);

    nlByte* dest = vec->data + (vec->length * vec->element_size);

    for (size_t i = 0; i < vec->element_size; i++) {
        dest[i] = elt[i];
    }

    vec->length++;
}
#else
    ;
#endif

#define nlVec_Push(vec, elt) nlVec_PushGeneric((vec), (nlByte*)&(elt))

#define nlVec_PushConst(vec, T, value)                                                                                 \
    do {                                                                                                               \
        T copy = (value);                                                                                              \
        nlVec_Push((vec), copy);                                                                                       \
    } while (0)

#endif
