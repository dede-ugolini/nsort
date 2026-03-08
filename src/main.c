#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "nsort.h"
#include "sort.h"

int main(int argc, char *argv[]) {
  Config config = parse_command_line(argc, argv);
  int fps = config.fps;
  srand(time(NULL));

  init_ncurses();
  int y, x;
  getmaxyx(stdscr, y, x);
  Column columns[x];
  for (int i = 0; i < x; i++) {
    columns[i].height = (rand() % (y - 1)) + 1;
    columns[i].color = WHITE;
    columns[i].draw = draw;
  }
  char *algorithm;
  Metrics metrics;
  switch (config.algorithm) {
  case SORT_SHELL:
    algorithm = "Shell sort";
    mvprintw(0, 0, "Algorithm: %s, fps: %d, lines: %d, columns: %d", algorithm,
             fps, y, x);
    refresh();
    getch();
    draw_columns(columns, y, x, fps);
    shell_sort(columns, x, y, fps);
    break;
  case SORT_INSERTION:
    algorithm = "Insertion sort";
    mvprintw(0, 0, "Algorithm: %s, fps: %d, lines: %d, columns: %d", algorithm,
             fps, y, x);
    refresh();
    getch();
    draw_columns(columns, y, x, fps);
    metrics = insertion_sort(columns, x, y, fps);
    break;
  case SORT_BOGO:
    algorithm = "Bogo sort";
    mvprintw(0, 0, "Algorithm: %s, fps: %d, lines: %d, columns: %d", algorithm,
             fps, y, x);
    refresh();
    getch();
    draw_columns(columns, y, x, fps);
    bogo_sort(columns, x, y, fps);
    break;
  case SORT_MERGE:
    break;
  case SORT_SELECTION:
    algorithm = "Selection sort";
    mvprintw(0, 0, "Algorithm: %s, fps: %d, lines: %d, columns: %d", algorithm,
             fps, y, x);
    refresh();
    getch();
    draw_columns(columns, y, x, fps);
    metrics = selection_sort(columns, x, y, fps);
    break;
  case SORT_BUBBLE:
  default:
    algorithm = "Bubble sort";
    mvprintw(0, 0, "Algorithm: %s, fps: %d, lines: %d, columns: %d", algorithm,
             fps, y, x);
    mvprintw(1, 0, "Press any key to start...!");
    refresh();
    getch();
    draw_columns(columns, y, x, fps);
    metrics = bubble_sort(columns, x, y, fps);
    break;
  }
  refresh();
  mvprintw(0, 0, "%s", algorithm);
  mvprintw(1, 0, "Done!");
  mvprintw(2, 0, "Swaps: %lld, Comparasions: %lld, Time: %f, size of array: %d",
           metrics.swaps, metrics.comparasions, metrics.time, x);
  mvprintw(3, 0, "Press any key to exit...!");
  getch();
  clear();
  endwin();
  return EXIT_SUCCESS;
}
