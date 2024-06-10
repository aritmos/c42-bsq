#include "utils.h"

ssize_t ft_atoui(const char *buf, size_t nbytes) {
  int i;
  ssize_t result;

  result = 0;
  while (i < nbytes) {
    if (buf[i] < '0' || '9' < buf[i])
      return -1;
    result = result * 10 + (buf[i] - '0');
    i++;
  }
  if (buf[0] == '0')
    return -1;
  return result;
}

inline bool char_is_printable(char c) { return 33 <= c && c <= 126; }
