#include "sort.h"
#include "nsort.h"

#include <ncurses.h>
#include <time.h>
#include <unistd.h>

Metrics selection_sort(Column columns[], int size, int y, int fps) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  long long comparasions = 0;
  long long swaps = 0;
  Column min;
  int minIndex;
  int interval = SECOND / fps;
  for (int i = 0; i < size - 1; i++) {
    min = columns[i];
    minIndex = i;
    for (int j = i + 1; j < size; j++) {
      columns[j].color = YELLOW;
      columns[j].draw(columns[j], y, j);
      columns[minIndex].color = RED;
      columns[minIndex].draw(columns[minIndex], y, minIndex);
      mvprintw(0, 0, "Selection Sort");
      refresh();
      usleep(interval);
      columns[j].color = WHITE;
      columns[j].draw(columns[j], y, j);
      if (columns[j].height < min.height) {
        columns[minIndex].color = WHITE;
        columns[minIndex].draw(columns[minIndex], y, minIndex);
        min = columns[j];
        minIndex = j;
        ++comparasions;
      }
    }

    swap_columns(&columns[i], &columns[minIndex]);
    ++swaps;

    columns[minIndex].color = WHITE;
    columns[minIndex].draw(columns[minIndex], y, minIndex);
    columns[i].color = GREEN;
    columns[i].draw(columns[i], y, i);
  }
  columns[size - 1].color = GREEN;
  columns[size - 1].draw(columns[size - 1], y, size - 1);
  clock_gettime(CLOCK_MONOTONIC, &end);
  double elapsed =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  Metrics metrics = {
      comparasions,
      swaps,
      elapsed,
  };
  return metrics;
}

Metrics bubble_sort(Column columns[], int size, int y, int fps) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  long long comparasions = 0;
  long long swaps = 0;
  int interval = SECOND / fps;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      columns[j].color = GREEN;
      columns[j].draw(columns[j], y, j);
      refresh();
      usleep(interval);
      if (columns[j].height > columns[j + 1].height) {
        swap_columns(&columns[j], &columns[j + 1]);
        ++swaps;
      }
      ++comparasions;
      columns[j].color = WHITE;
      columns[j].draw(columns[j], y, j);
      refresh();
    }
    columns[size - i - 1].color = RED;
    columns[size - i - 1].draw(columns[size - i - 1], y, size - i - 1);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double elapsed =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  Metrics metrics = {
      comparasions,
      swaps,
      elapsed,
  };
  return metrics;
}

// FIX: No canto inferior esquerdo, as vezes sobra uma rebarba que não foi
// ordenada corretamente
Metrics insertion_sort(Column columns[], int size, int y, int fps) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  long long comparasions = 0;
  long long swaps = 0;
  int i, j;
  int interval = SECOND / fps;
  for (i = 0; i < size; i++) {
    ++comparasions;
    for (j = i + 1; j > 0 && columns[j].height < columns[j - 1].height; j--) {
      columns[j].color = YELLOW;
      columns[j - 1].color = GREEN;
      columns[j].draw(columns[j], y, j);
      columns[j - 1].draw(columns[j - 1], y, j - 1);
      swap_columns(&columns[j], &columns[j - 1]);
      ++swaps;
      mvprintw(0, 0, "Insertion Sort");
      usleep(interval);
      columns[j].color = GREEN;
      columns[j - 1].color = GREEN;
      columns[j].draw(columns[j], y, j);
      columns[j - 1].draw(columns[j], y, j - 1);
      refresh();
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double elapsed =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  Metrics metrics = {
      comparasions,
      swaps,
      elapsed,
  };
  return metrics;
}
