#include <stdlib.h>

#include "nvector.h"

int nv__init (nvector* nv, size_t initial_length, size_t elt_size)
{
  nv->elt_size = elt_size;
  nv->capacity = initial_length * nv->elt_size;
  nv->buffer = malloc (nv->capacity);
  nv->length = 0;

  return nv->buffer == NULL ? NV_ERR_MEM : NV_ERR_OK;
}

void nv_free (nvector* nv)
{
  if (nv->buffer != NULL)
    {
      free (nv->buffer);
      nv->buffer = NULL;
    }
}

int nv_trim (nvector* nv)
{
  if (nv == NULL || nv->buffer == NULL)
    return NV_ERR_MEM;

  nv->capacity = nv->length * nv->elt_size;

  if (nv->capacity == 0) /* prevent nullifying the pointer */
    nv->buffer = realloc (nv->buffer, 1);
  else
    nv->buffer = realloc (nv->buffer, nv->capacity);

  return nv->buffer == NULL ? NV_ERR_MEM : NV_ERR_OK;
}

int nv__pushb (nvector* nv, unsigned int elt_size, char* value)
{
  if (nv == NULL)
    return NV_ERR_MEM;
  else
    return nv__insert (nv, elt_size, nv->length, value);
}

int nv__set (nvector* nv, unsigned int elt_size, size_t pos, char* value)
{
  unsigned int i;

  if (nv == NULL || nv->buffer == NULL || value == NULL)
    return NV_ERR_MEM;

  if (elt_size != nv->elt_size)
    return NV_ERR_TYPE;

  if (pos >= nv->length)
    return NV_ERR_IDX;

  /* Copy the element into the buffer. */
  for (i = 0; i < elt_size; i++)
    nv->buffer[nv->elt_size * pos + i] = value[i];

  /* Fill the rest of the cell with zeroes. */
  for (; i < nv->elt_size; i++)
    nv->buffer[nv->elt_size * pos + i] = 0;

  return NV_ERR_OK;
}

#define BUFFER 10

int nv__insert (nvector* nv, unsigned int elt_size, size_t pos, char* value)
{
  unsigned int i;

  if (nv == NULL || nv->buffer == NULL || value == NULL)
    return NV_ERR_MEM;

  if (elt_size != nv->elt_size)
    return NV_ERR_TYPE;

  if (pos > nv->length) /* exclusive to support pushing back */
    return NV_ERR_IDX;

  /* Make sure there is enough memory for the new element. */
  if (nv->length * nv->elt_size >= nv->capacity)
    {
      nv->capacity = nv->elt_size * (nv->length + BUFFER);
      nv->buffer = realloc (nv->buffer, nv->capacity);

      if (nv->buffer == NULL)
        return NV_ERR_MEM;
    }

  /* Shift the entire buffer by one cell. */
  if (pos > 0)
    {
      i = nv->length * nv->elt_size;

      while (i >= (pos + 1) * nv->elt_size)
        {
          i--;
          nv->buffer[i] = nv->buffer[i - nv->elt_size];
        }
    }

  /* Copy VALUE into the buffer. */
  for (i = 0; i < elt_size; i++)
    nv->buffer[nv->elt_size * pos + i] = value[i];

  /* Fill the rest of the cell with zeroes. */
  for (; i < nv->elt_size; i++)
    nv->buffer[nv->elt_size * pos + i] = 0;

  nv->length++;

  return NV_ERR_OK;
}

#undef BUFFER
