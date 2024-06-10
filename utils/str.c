#include "utils.h"

t_str *vec_to_str(t_vec *vec) {
  char *buf;
  t_str *str;

  str = malloc(sizeof(*str));
  if (str == NULL)
    return NULL;
  buf = malloc(vec->len);
  if (buf == NULL)
    return NULL;
  str->buf = buf;
  ft_memcpy(str->buf, vec->buf, vec->len);
  str->len = vec->len;
  return str;
}

inline void str_drop(t_str *str) {
  free(str->buf);
  free(str);
}
