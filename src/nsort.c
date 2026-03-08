#include "nsort.h"
#include <getopt.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

void swap_columns(Column *a, Column *b) {
  Column tmp = *a;
  *a = *b;
  *b = tmp;
}

void draw(Column column, int y, int x) {
  int height = column.height;
  int color = column.color;

  attron(COLOR_PAIR(BLACK));
  for (int i = 0; i < y; i++) {
    mvprintw(i, x, " ");
    refresh();
  }
  attroff(COLOR_PAIR(BLACK));

  attron(COLOR_PAIR(color));
  while (height > 0) {
    mvprintw(y - height, x, " ");
    height--;
  }
  attroff(COLOR_PAIR(color));
}

void draw_columns(Column columns[], int y, int x, int fps) {
  int interval = SECOND / fps;
  for (int i = 0; i < x; i++) {
    columns[i].draw(columns[i], y, i);
    usleep(interval);
  }
}

void init_ncurses() {
  initscr();
  curs_set(false);
  start_color();
  init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
  init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
  init_pair(RED, COLOR_RED, COLOR_RED);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
  init_pair(CYAN, COLOR_CYAN, COLOR_CYAN);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
}

static void help(int status) {
  printf("Usage: %s [OPTIONS]\n", progname);
  printf("Options:\n");
  printf("  -h, --help           Show this help\n");
  printf("  -b, --bubble         Use bubble sort (default)\n");
  printf("  -i, --insertion      Use insertion sort\n");
  printf("  -g, --bogo           Use bogo sort\n");
  printf("  -s, --selection      Use selection sort\n");
  printf("  -l, --shell          Use shell sort\n");
  printf("  -q, --quick          Use quick sort\n");
  printf(
      "  -r, --reverse        Use algorithms sort reverse (default false)\n");
  printf("  -f, --fps <number>   Frames per second (default 60)\n");
  exit(status);
}

Config parse_command_line(int argc, char **argv) {
  int opt;
  char *end;
  long fps;
  Config config = {60, SORT_BUBBLE, false};
  struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"bubble", no_argument, 0, 'b'},
      {"insertion", no_argument, 0, 'i'},
      {"bogo", no_argument, 0, 'g'},
      {"merge", no_argument, 0, 'm'},
      {"selection", no_argument, 0, 's'},
      {"shell", no_argument, 0, 'l'},
      {"quick", no_argument, 0, 'q'},
      {"reverse", no_argument, 0, 'r'},
      {"fps", required_argument, 0, 'f'},
      {0, 0, 0, 0},
  };
  while ((opt = getopt_long(argc, argv, "hbigmslqrf:", long_options, NULL)) !=
         -1) {
    switch (opt) {
    case 'h':
      help(EXIT_SUCCESS);
      break;
    case 'b':
      config.algorithm = SORT_BUBBLE;
      break;
    case 'i':
      config.algorithm = SORT_INSERTION;
      break;
    case 'g':
      config.algorithm = SORT_BOGO;
      break;
    case 'm':
      config.algorithm = SORT_MERGE;
      break;
    case 's':
      config.algorithm = SORT_SELECTION;
      break;
    case 'l':
      config.algorithm = SORT_SHELL;
      break;
    case 'q':
      config.algorithm = SORT_QUICK;
      break;
    case 'r':
      config.reverse = true;
      break;
    case 'f':
      fps = strtol(optarg, &end, 10);
      if (*end != '\0' || fps <= 0) {
        fprintf(stderr, "Invalid fps value: %s\n", optarg);
        exit(EXIT_FAILURE);
      }
      config.fps = (int)fps;
      break;
    }
  }
  return config;
}
