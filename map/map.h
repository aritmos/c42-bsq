#ifndef MAP_H
#define MAP_H

#include "../utils/utils.h"

// --- TYPES ------------------------------------------------------------------

// NOTE: `cols` includes `\n`s.
// NOTE: `buf` is a valid buffer of size `rows * cols`
typedef struct s_map {
  size_t rows;
  size_t cols;
  char symbols[3];
  char *buf;
} t_map;

typedef struct s_legend {
  size_t rows;
  char symbols[3];
} t_legend;

// --- MAP --------------------------------------------------------------------

// Creates the map's buffer.
// SAFETY: Caller guarantess that `map->rows` and `map->cols` are corretly
// instantiated.
bool map_create_buff(t_map *map);

// Gets a char from the given map.
// SAFETY: The caller must guarantee that `map` is a valid pointer,
// (the map and its buffer have been instantiated).
char map_get(t_map *map, size_t row, size_t col);

// Gets the pointer to the specified position in the map's buffer.
// SAFETY: The caller must guarantee that `map` is a valid pointer,
// (the map and its buffer have been instantiated).
char *map_get_ptr(t_map *map, size_t row, size_t col);

// --- VALIDATE ---------------------------------------------------------------

bool parse_legend(t_legend *legend, const char *buf, size_t nbytes);

bool map_buff_is_valid(t_map *map);

#endif
