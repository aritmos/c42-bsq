#include "utils.h"

ssize_t read_line(int fd, char *buf, size_t buf_size) {
  int i;
  ssize_t bytes_read;

  i = 0;
  while (i < buf_size) {
    bytes_read = read(fd, buf + i, 1);
    if (bytes_read == -1)
      return -1;
    if (bytes_read == 0 || buf[i] == '\n')
      break;
    i++;
  }
  return i;
}

ssize_t read_line_vec(int fd, t_vec *vec) {
  ssize_t bytes_read;
  bool ok;

  bytes_read = 0;
  while (true) {
    ok = read_char_vec(fd, vec);
    if (!ok)
      return -1;
    bytes_read += 1;
    if (vec->buf[vec->len - 1] == '\n')
      break;
  }
  return bytes_read;
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
