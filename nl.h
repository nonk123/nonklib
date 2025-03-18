#ifndef NL_H
#define NL_H

#include <stdlib.h>

#ifndef NL_Allocate
#define NL_Allocate malloc
#endif

#ifndef NL_Free
#define NL_Free free
#endif

typedef unsigned char NL_Byte;

typedef struct NL_Vec NL_Vec;
struct NL_Vec {
    NL_Byte* data;
    size_t length, capacity, element_size;
};

#define NL_VecOf(T)                                                                                \
    (NL_Vec) {                                                                                     \
        .data = NULL, .length = 0, .capacity = 0, .element_size = sizeof(T),                       \
    }

void NL_Vec_Free(NL_Vec* vec)
#ifdef NL_IMPLEMENTATION
{
    if (vec->data != NULL) {
        NL_Free(vec->data);
        vec->data = NULL;
        vec->length = 0;
        vec->capacity = 0;
    }
}
#else
    ;
#endif

#define NL_Vec_BASE_CAPACITY (512)
#define NL_Vec_GROWTH_FACTOR (2)

void NL_Vec_MaybeInit(NL_Vec* vec)
#ifdef NL_IMPLEMENTATION
{
    if (vec->data == NULL) {
        vec->data = NL_Allocate(NL_Vec_BASE_CAPACITY * vec->element_size);
        vec->capacity = NL_Vec_BASE_CAPACITY;
    }
}
#else
    ;
#endif

void NL_Vec_MaybeGrow(NL_Vec* vec)
#ifdef NL_IMPLEMENTATION
{
    NL_Vec_MaybeInit(vec);

    if (vec->length < vec->capacity) {
        return;
    }

    NL_Byte* old_data = vec->data;
    vec->data = NL_Allocate(vec->capacity * vec->element_size * NL_Vec_GROWTH_FACTOR);

    for (size_t i = 0; i < vec->capacity * vec->element_size; i++) {
        vec->data[i] = old_data[i];
    }

    vec->capacity *= NL_Vec_GROWTH_FACTOR;
    NL_Free(old_data);
}
#else
    ;
#endif

void NL_Vec_PushGeneric(NL_Vec* vec, const NL_Byte* elt)
#ifdef NL_IMPLEMENTATION
{
    NL_Vec_MaybeGrow(vec);

    NL_Byte* dest = vec->data + (vec->length * vec->element_size);

    for (size_t i = 0; i < vec->element_size; i++) {
        dest[i] = elt[i];
    }

    vec->length++;
}
#else
    ;
#endif

#define NL_Vec_Push(vec, elt) NL_Vec_PushGeneric((vec), (NL_Byte*)&(elt))

#define NL_Vec_PushConst(vec, T, value)                                                            \
    do {                                                                                           \
        T copy = (value);                                                                          \
        NL_Vec_Push((vec), copy);                                                                  \
    } while (0)

#endif
