#ifndef NVECTOR_H
#define NVECTOR_H

typedef struct nvector nvector;
struct nvector
{
  char* buffer; /* a generalized buffer for arbitrary data */
  size_t length, capacity;
  unsigned int elt_size; /* size of one element in bytes */
};

#define NV_ERR_OK   0 /* everything went ok */
#define NV_ERR_MEM  1 /* memory error: the vector or its buffer is NULL */
#define NV_ERR_TYPE 2 /* type mismatch: vector cannot hold such big values */
#define NV_ERR_IDX  3 /* out-of-bounds index error */

/* Define a set of generic functions for specified datatype. */
#define nv_generic(suffix, type, indirection)                   \
  /* Initialize a vector's buffer. */                           \
  int nv_init_##suffix (nvector* nv, size_t initial_length)     \
  { return nv__init (nv, initial_length, sizeof (type)); }      \
  /* Insert VALUE into the Nth cell. */                         \
  int nv_insert_##suffix (nvector* nv, size_t n, type value)    \
  { return nv__insert (nv, sizeof (type), n, (char*) &value); } \
  /* Push VALUE to the end of the vector. */                    \
  int nv_pushb_##suffix (nvector* nv, type value)               \
  { return nv__pushb (nv, sizeof (type), (char*) &value); }     \
  /* Push VALUE to the start of the vector. */                  \
  int nv_pushf_##suffix (nvector* nv, type value)               \
  { return nv_insert_##suffix (nv, 0, value); }                 \
  /* Retrieve the Nth element of the vector. */                 \
  type nv_get_##suffix (nvector* nv, size_t n)                  \
  { return indirection (type*) &nv->buffer[nv->elt_size * n]; } \
  /* Replace the Nth element of the vector with VALUE. */       \
  int nv_set_##suffix (nvector* nv, size_t n, type value)       \
  { return nv__set (nv, sizeof (type), n, (char*) &value); }

/* Define generic functions for a value type. */
#define nv_value(simple_type)                   \
  nv_generic (simple_type, simple_type, *)

/* Define generic functions for a pointer type, suffixed with _p. */
#define nv_ptr(base_type, indirection)                              \
  nv_generic (base_type##_p, base_type indirection, indirection)

/* Public functions. */

/* Trim a vector's buffer exactly to its length. */
int nv_trim (nvector*);

/* Free a vector's buffer. The vector can then be reused in nv_init_*. */
void nv_free (nvector*);

/* Internal functions. */

int nv__init (nvector*, size_t initial_length, size_t elt_size);
int nv__insert (nvector*, unsigned int elt_size, size_t pos, char* value);
int nv__set (nvector*, unsigned int elt_size, size_t pos, char* value);
int nv__pushb (nvector*, unsigned int elt_size, char* value);

#endif /* NVECTOR_H */
