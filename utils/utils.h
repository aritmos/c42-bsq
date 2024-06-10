#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// --- TYPES ------------------------------------------------------------------

typedef struct s_str {
  char *buf;
  size_t len;
} t_str;

typedef struct s_vec {
  char *buf;
  size_t len;
  size_t cap;
} t_vec;

// --- MEMORY -----------------------------------------------------------------

void ft_memcpy(char *dest, const char *src, size_t count);

// --- STR --------------------------------------------------------------------

// Copies the contents of a vec into a string.
// SAFETY: may return `NULL`.
t_str *vec_to_str(t_vec *vec);

// Drops the string (and its internal buffer).
void str_drop(t_str *str);

// --- VEC --------------------------------------------------------------------

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

// Reads a line from the given file descriptor into a string.
// Returns `NULL` if it got to EOF before finding a newline or if errored
// internally.
t_str *read_line(int fd);

// Reads a char from the given file descriptor into char.
// Returns `true` if it correctly read the char, and `false` if if could not
// read a char (error or EOF) or had any other internal error.
bool read_char_vec(int fd, t_vec *vec);

// --- PARSING ----------------------------------------------------------------

// Parses an unsigned int, returns `-1` if the format was invalid.
ssize_t ft_atoui(const char *buf, size_t nbytes);

// Returns `true` if a char is printable (visible), else `false`.
bool char_is_printable(char c);

#endif
