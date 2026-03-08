#include "sort.h"
#include "nsort.h"

#include <ncurses.h>
#include <stdlib.h>
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

Metrics selection_sort_reverse(Column columns[], int size, int y, int fps) {
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
      if (columns[j].height > min.height) {
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

Metrics bubble_sort_reverse(Column columns[], int size, int y, int fps) {
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
      if (columns[j].height < columns[j + 1].height) {
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

// FIX: Apos ordenar, programa cracheia com seg fault
Metrics insertion_sort_reverse(Column columns[], int size, int y, int fps) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  long long comparasions = 0;
  long long swaps = 0;
  int i, j;
  int interval = SECOND / fps;
  for (i = 0; i < size; i++) {
    ++comparasions;
    for (j = i + 1; j > 0 && columns[j].height > columns[j - 1].height; j--) {
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

static bool is_sorted(Column columns[], int size) {
  while (--size >= 1) {
    if (columns[size].height < columns[size - 1].height) {
      return false;
    }
  }
  return true;
}

static void shuffle(Column columns[], int size, int y, int fps) {
  int i, tmp, r;
  int interval = SECOND / fps;
  for (i = 0; i < size; i++) {
    tmp = columns[i].height;
    r = rand() % size;
    columns[i].height = columns[r].height;
    columns[r].height = tmp;
    columns[r].color = RED;
    columns[r].draw(columns[r], y, r);
    refresh();
    usleep(interval);
    refresh();
  }
}

void bogo_sort(Column columns[], int size, int y, int fps) {
  while (!is_sorted(columns, size)) {
    shuffle(columns, size, y, fps);
  }
}

void shell_sort(Column columns[], int size, int y, int fps) {
  int interval = SECOND / fps;
  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < size; i++) {
      Column tmp = columns[i];
      int j = i;

      while (j >= gap && columns[j - gap].height > tmp.height) {
        columns[j - gap].color = RED;
        columns[j - gap].draw(columns[j - gap], y, j - gap);
        columns[j].color = GREEN;
        columns[j].draw(columns[j], y, j);
        refresh();
        usleep(interval);
        swap_columns(&columns[j], &columns[j - gap]);
        columns[j - gap].color = BLUE;
        columns[j - gap].draw(columns[j - gap], y, j - gap);
        columns[j].color = YELLOW;
        columns[j].draw(columns[j], y, j);
        refresh();
        usleep(interval);
        j -= gap;
      }
      refresh();
    }
  }
  refresh();
}

void shell_sort_reverse(Column columns[], int size, int y, int fps) {
  int interval = SECOND / fps;
  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < size; i++) {
      Column tmp = columns[i];
      int j = i;

      while (j >= gap && columns[j - gap].height < tmp.height) {
        columns[j - gap].color = RED;
        columns[j - gap].draw(columns[j - gap], y, j - gap);
        columns[j].color = GREEN;
        columns[j].draw(columns[j], y, j);
        refresh();
        usleep(interval);
        swap_columns(&columns[j], &columns[j - gap]);
        columns[j - gap].color = BLUE;
        columns[j - gap].draw(columns[j - gap], y, j - gap);
        columns[j].color = YELLOW;
        columns[j].draw(columns[j], y, j);
        refresh();
        usleep(interval);
        j -= gap;
      }
      refresh();
    }
  }
  refresh();
}

void quick_sort(Column columns[], int low, int size, int y, int fps) {
  int interval = SECOND / fps;
  if (low > size) {
    return;
  }
  columns[size].color = BLUE;
  columns[size].draw(columns[size], y, size);
  int w = low - 1;
  int j = low;

  while (j != size) {
    columns[j].color = YELLOW;
    columns[j].draw(columns[j], y, j);

    columns[w + 1].color = RED;
    columns[w + 1].draw(columns[w + 1], y, w + 1);
    mvprintw(0, 0, "Quick Sort");
    refresh();
    usleep(interval);
    columns[j].color = WHITE;
    columns[j].draw(columns[j], y, j);

    if (columns[j].height < columns[size].height) {
      w++;
      columns[w].color = WHITE;
      columns[w].draw(columns[w], y, w);
      swap_columns(&columns[w], &columns[j]);
      columns[w].color = WHITE;
      columns[w].draw(columns[w], y, w);
      columns[j].draw(columns[j], y, j);
    }
    j++;
  }
  w++;
  swap_columns(&columns[w], &columns[size]);

  columns[size].color = WHITE;
  columns[size].draw(columns[size], y, size);
  columns[w].color = GREEN;
  columns[w].draw(columns[w], y, w);

  mvprintw(0, 0, "Quick Sort");
  refresh();
  usleep(interval);

  quick_sort(columns, low, w - 1, y, fps);
  quick_sort(columns, w + 1, size, y, fps);
  return;
}

void quick_sort_reverse(Column columns[], int low, int size, int y, int fps) {
  int interval = SECOND / fps;
  if (low > size) {
    return;
  }
  columns[size].color = BLUE;
  columns[size].draw(columns[size], y, size);
  int w = low - 1;
  int j = low;

  while (j != size) {
    columns[j].color = YELLOW;
    columns[j].draw(columns[j], y, j);

    columns[w + 1].color = RED;
    columns[w + 1].draw(columns[w + 1], y, w + 1);
    mvprintw(0, 0, "Quick Sort");
    refresh();
    usleep(interval);
    columns[j].color = WHITE;
    columns[j].draw(columns[j], y, j);

    if (columns[j].height > columns[size].height) {
      w++;
      columns[w].color = WHITE;
      columns[w].draw(columns[w], y, w);
      swap_columns(&columns[w], &columns[j]);
      columns[w].color = WHITE;
      columns[w].draw(columns[w], y, w);
      columns[j].draw(columns[j], y, j);
    }
    j++;
  }
  w++;
  swap_columns(&columns[w], &columns[size]);

  columns[size].color = WHITE;
  columns[size].draw(columns[size], y, size);
  columns[w].color = GREEN;
  columns[w].draw(columns[w], y, w);

  mvprintw(0, 0, "Quick Sort");
  refresh();
  usleep(interval);

  quick_sort(columns, low, w - 1, y, fps);
  quick_sort(columns, w + 1, size, y, fps);
  return;
}
