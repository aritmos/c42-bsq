#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// --- MEMORY -----------------------------------------------------------------

void ft_memcpy(char *dest, const char *src, size_t count);

// --- VEC --------------------------------------------------------------------

typedef struct s_vec {
  char *buf;
  size_t len;
  size_t cap;
} t_vec;

// Creates a new `t_vec` and stores it in the given pointer.
// Returns `true` if succeeded, `false` if errored.
// SAFETY: Caller guarantees `vec` is a valid pointer.
bool vec_create(t_vec *vec, size_t cap);

// Grows a `t_vec` into a certain capacity.
// Returns `true` if `new_cap <= vec->cap` or if succeeded, `false` if errored.
// NOTE: Does nothing if `new_cap <= vec->cap`.
// SAFETY: Caller guarantees `vec` is a valid pointer.
bool vec_grow(t_vec *vec, size_t new_cap);

// Pushes an element to the back of the vector, possibly regrowing it if needed.
// Returns `false` if an error occurred.
// SAFETY: Caller guarantees `vec` is a valid pointer.
bool vec_push(t_vec *vec, char c);

// Checks if a vec has enough space
bool vec_has_space(const t_vec *vec, size_t nbytes);

// --- I/O --------------------------------------------------------------------

// Reads a line from the given file descriptor into a buffer.
// Ends reading once it has filled the buffer or encountered a newline
// character. Returns the number of read bytes or `-1` if an error occurred.
// SAFETY: Caller ensures (by magic) that `buf` is large enough for
// the line that is to be written to it.
ssize_t read_line(int fd, char *buf, size_t buf_size);

// Reads a line dynamically into a `t_vec` (including the `\n`), growing it as
// needed. Returns the number of read bytes (including `\n`) or `-1` if an error
// occurred.
// SAFETY: Caller guarantees `vec` is a valid pointer.
ssize_t read_line_vec(int fd, t_vec *vec);

// Reads a char from the given file descriptor into char.
// Returns `true` if it correctly read the char, and `false` if if could not
// read a char (error or EOF) or had any other internal error.
bool read_char_vec(int fd, t_vec *vec);

#endif
