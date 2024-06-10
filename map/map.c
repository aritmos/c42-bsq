#include "map.h"

bool map_create_buff(t_map *map) {
  char *buff;

  buff = (char *)malloc(map->rows * map->cols);
  if (buff == NULL)
    return false;
  map->buf = buff;
  return true;
}

inline char map_get(t_map *map, size_t row, size_t col) {
  return map->buf[row * map->cols + col];
}

inline char *map_get_ptr(t_map *map, size_t row, size_t col) {
  return map->buf + row * map->cols + col;
}

void map_set_legend(t_map *map, const t_legend *legend) {
  map->rows = legend->rows;
  ft_memcpy(map->symbols, legend->symbols, 3);
}

bool map_init_legend(t_map *map, int fd) {
  t_str *line;
  t_legend legend;
  bool ok;

  line = read_line(fd);
  if (line == NULL)
    return false;
  ok = parse_legend(&legend, line->buf, line->len);
  if (!ok)
    return false;
  str_drop(line);
  map_set_legend(map, &legend);
  return true;
}

bool map_init_buf(t_map *map, int fd) {
  t_str *line;
  size_t read_bytes;
  size_t remaining_bytes;

  line = read_line(fd);
  if (line == NULL || line->len == 1)
    return false;
  map->cols = line->len;
  map_create_buff(map);
  ft_memcpy(map->buf, line->buf, line->len);
  remaining_bytes = (map->rows - 1) * map->cols;
  read_bytes = read(fd, map_get_ptr(map, 1, 0), remaining_bytes);
  if (read_bytes != remaining_bytes)
    return false;
  str_drop(line);
  return true;
}

// Instantiates a map from the given file
bool map_init(t_map *map, int fd) {
  bool ok;
  char test_buff;

  ok = map_init_legend(map, fd);
  if (!ok)
    false;
  ok = map_init_buf(map, fd);
  if (!ok)
    return false;
  ok = (0 == read(fd, &test_buff, 1));
  if (!ok)
    return false;
  ok = map_buff_is_valid(map);
  return ok;
}
