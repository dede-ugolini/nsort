#ifndef NSORT_H
#define NSORT_H

#define progname "nsort"
#define SECOND 1000000

enum Colors { BLACK, WHITE, RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA };

typedef enum {
  SORT_BUBBLE,
  SORT_INSERTION,
  SORT_BOGO,
  SORT_MERGE,
  SORT_SELECTION,
  SORT_SHELL,
} Sort_Algorithm;

typedef struct {
  int fps;
  Sort_Algorithm algorithm;
} Config;

typedef struct {
  long long comparasions;
  long long swaps;
  double time;
} Metrics;

typedef struct Column Column;

struct Column {
  int height;
  enum Colors color;
  void (*draw)(Column column, int y, int x);
};

void draw(Column column, int y, int x);

void draw_columns(Column columns[], int y, int x, int fps);

void swap_columns(Column *a, Column *b);

void init_ncurses();

Config parse_command_line(int argc, char **argv);

#endif
