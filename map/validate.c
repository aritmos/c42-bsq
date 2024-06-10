#include "map.h"

// Returns `true` if the symbols are valid for a map, else `false`.
bool valid_symbols(const char symbols[3]) {
  bool chars_all_different;
  bool chars_all_printable;

  chars_all_different = symbols[0] != symbols[1] && symbols[1] != symbols[2] &&
                        symbols[0] != symbols[2];
  chars_all_printable = char_is_printable(symbols[0]) &&
                        char_is_printable(symbols[1]) &&
                        char_is_printable(symbols[2]);
  return chars_all_different && chars_all_printable;
}

// Parses (and validates) the legend, returns `true` if succeeded, else `false`.
// NOTE: `nbytes` does not include the `\n`.
bool parse_legend(t_legend *legend, const char *buf, size_t nbytes) {
  bool symbols_are_valid;
  ssize_t rows;

  if (nbytes < 4)
    return false;
  symbols_are_valid = valid_symbols(&buf[nbytes - 3]);
  rows = ft_atoui(buf, nbytes - 3);
  if (!symbols_are_valid || rows == -1)
    return false;
  legend->rows = (size_t)rows;
  ft_memcpy(legend->symbols, &buf[nbytes - 3], 3);
  return true;
}

// Validates the map's buffer.
// - 1. Actual map only contains the valid symbols
// - 2. All rows end in a newline
// SAFETY: This function does not guarantee that the the parsing is correct,
// namely the buffer could not have been fully filled, or the input file could
// contain more bytes. This function should be called after checking
// - 1. that the number of copied bytes into the buffer is equal to the size of
// the buffer.
// - 2. that there are no remaining bytes in the input file.
bool map_buff_is_valid(t_map *map) {
  size_t row;
  size_t col;
  char c;

  while (row < map->rows) {
    while (col < map->cols - 1) {
      c = map_get(map, row, col);
      if (c != map->symbols[0] && c != map->symbols[1])
        return false;
      col++;
    }
    if (map_get(map, row, map->cols - 1) != '\n')
      return false;
  }
}
