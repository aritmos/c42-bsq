#include "utils.h"

bool vec_create(t_vec *vec, size_t cap) {
  vec->buf = malloc(cap);
  vec->len = 0;
  vec->cap = cap;

  return (vec->buf != NULL);
}

bool vec_grow(t_vec *vec, size_t new_cap) {
  char *new_buf;

  if (new_cap <= vec->cap)
    return true;
  new_buf = malloc(new_cap);
  if (vec->buf == NULL)
    return false;
  ft_memcpy(new_buf, vec->buf, vec->len);
  vec->buf = new_buf;
  vec->cap = new_cap;
  return true;
}

bool vec_push(t_vec *vec, char c) {
  bool grow_ok;

  if (vec->len == vec->cap) {
    grow_ok = vec_grow(vec, vec->cap * 2);
    if (!grow_ok)
      return false;
  }
  vec->buf[vec->len] = c;
  vec->len++;
  return true;
}

inline bool vec_has_space(const t_vec *vec, size_t nbytes) {
  return (vec->cap - vec->len) >= nbytes;
}
