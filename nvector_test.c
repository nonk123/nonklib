#include <stdio.h>

#include "nvector.h"

typedef struct foo foo;
struct foo
{
  int a, b;
};

/* Define generic functions for the following types. */
nv_value (int);
nv_value (double);
nv_value (foo);
nv_ptr (foo, *);

int
test_square (nvector* vec)
{
  int i;

  /* Create a new vector of, initially, 10 integers. */
  if (nv_init_int (vec, 10) == NV_ERR_MEM)
    {
      puts ("memory allocation error");
      return 1;
    }

  puts ("time to square some integers!\n");

  /* Put 15 squared integers at the end of the vector. */
  for (i = 1; i <= 15; i++)
    {
      if (nv_pushb_int (vec, i * i) != NV_ERR_OK)
        {
          puts ("nv_pushb_int failed");
          return 1;
        }
    }

  /* Print all the squares out. */
  for (i = 0; i < 15; i++)
    printf ("vec[%d] = %d\n", i, nv_get_int (vec, i));

  /* Double is bigger than integer, so pushing should result in an error. */
  if (nv_pushb_double (vec, 420.69) == NV_ERR_OK)
    {
      puts ("\nnv_pushb_double succeeded (very bad)");
      return 1;
    }
  else
    puts ("\nnv_pushb_double failed (good)");

  /* Deallocate the vector's buffer. The vector is still usable. */
  nv_free (vec);
  return 0;
}

int
test_double (nvector* vec)
{
  /* Refit the vector for 5 double values. */
  if (nv_init_double (vec, 5) == NV_ERR_MEM)
    {
      puts ("memory allocation error");
      return 1;
    }

  puts ("\nvector refitted for double values\n");

  /* Put a value inside the vector. */
  nv_pushf_double (vec, 42.0);
  printf ("a very good rational number: %.1f\n", nv_get_double (vec, 0));

  /* Replace it with another one. */
  nv_set_double (vec, 0, 420.69);
  printf ("a great rational number: %.2f\n", nv_get_double (vec, 0));

  /* Setting a value outside of vector's length is an error. */
  if (nv_set_double (vec, 1, 420.69) == NV_ERR_IDX)
    puts ("\nnv_set_double failed (good)");
  else
    {
      puts ("\nnv_set_double succeeded (very bad)");
      return 1;
    }

  nv_free (vec);
  return 0;
}

int
test_foo (nvector* vec)
{
  foo f;
  int other_a;

  /* Refit to the foo struct. */
  if (nv_init_foo (vec, 5) == NV_ERR_MEM)
    {
      puts ("memory allocation error");
      return 1;
    }

  puts ("\nrefitted to foo\n");

  f.a = 42;
  f.b = 69;

  /* Push a copy of f. */
  nv_pushf_foo (vec, f);

  f.a = 1337;

  other_a = nv_get_foo (vec, 0).a;
  printf ("the foos' a's are different: %d and %d\n", f.a, other_a);

  nv_free (vec);
  return 0;
}

int
test_foo_ptr (nvector* vec)
{
  foo f;
  int other_a;

  if (nv_init_foo_p (vec, 5) == NV_ERR_MEM)
    {
      puts ("memory allocation error");
      return 1;
    }

  puts ("\nfoo pointer incoming!\n");

  /* Push a pointer to f. */
  nv_pushf_foo_p (vec, &f);

  f.a = 69420;
  other_a = nv_get_foo_p (vec, 0)->a;

  printf ("should be the same: %d and %d\n", f.a, other_a);

  nv_free (vec);
  return 0;
}

int
test_trim (nvector* vec)
{
  /* The final trick: trimming. */
  if (nv_init_int (vec, 100) == NV_ERR_MEM)
    {
      puts ("memory allocation error");
      return 1;
    }

  puts ("\ntrimming tricks\n");

  printf ("initial capacity: %d\n", vec->capacity);

  if (nv_trim (vec) == NV_ERR_MEM)
    {
      puts ("trimming failed");
      return 1;
    }

  /* It should reset to 0. */
  printf ("capacity after trimming: %d\n", vec->capacity);

  /* We can still add more elements and expand the buffer. */
  nv_pushf_int (vec, 128);
  printf ("capacity after pushing: %d\n", vec->capacity);

  /* Deallocate the buffer for good. */
  nv_free (vec);
  return 0;
}

int
main ()
{
  nvector vec;

  return test_square (&vec) || test_double (&vec) || test_foo (&vec)
         || test_foo_ptr (&vec) || test_trim (&vec);
}
