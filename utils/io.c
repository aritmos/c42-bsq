#include "utils.h"

t_str *read_line(int fd) {
  t_vec vec;
  t_str *str;
  ssize_t bytes_read;
  bool ok;

  bytes_read = 0;
  ok = vec_create(&vec, 4);
  if (!ok)
    return NULL;
  while (true) {
    ok = read_char_vec(fd, &vec);
    if (!ok)
      return NULL;
    bytes_read += 1;
    if (vec.buf[vec.len - 1] == '\n')
      break;
  }
  str = vec_to_str(&vec);
  free(vec.buf);

  return vec_to_str(&vec);
}

bool vec_read_char(int fd, t_vec *vec) {
  bool ok;
  ssize_t read_ret;

  if (!vec_has_space(vec, 1)) {
    ok = vec_grow(vec, vec->cap * 2);
    if (!ok)
      return false;
  }
  read_ret = read(fd, vec->buf + vec->len, 1);
  vec->len++;
  if (read_ret <= 1)
    return false;

  return true;
}
