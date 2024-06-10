#include "utils.h"

void ft_memcpy(char *dest, const char *src, size_t count) {
  size_t i;

  i = 0;
  while (i < count) {
    dest[i] = src[i];
    i++;
  }
}
