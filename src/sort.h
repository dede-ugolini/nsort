#ifndef SORT_H
#define SORT_H

#include "nsort.h"

Metrics selection_sort(Column columns[], int size, int y, int fps);

Metrics selection_sort_reverse(Column columns[], int size, int y, int fps);

Metrics bubble_sort(Column columns[], int size, int y, int fps);

Metrics bubble_sort_reverse(Column columns[], int size, int y, int fps);

Metrics insertion_sort(Column columns[], int size, int y, int fps);

Metrics insertion_sort_reverse(Column columns[], int size, int y, int fps);

void bogo_sort(Column columns[], int size, int y, int fps);

void shell_sort(Column columns[], int size, int y, int fps);

void shell_sort_reverse(Column columns[], int size, int y, int fps);

void quick_sort(Column columns[], int low, int size, int y, int fps);

void quick_sort_reverse(Column columns[], int low, int size, int y, int fps);

void merge_sort(Column columns[], int low, int y, int right, int fps);

#endif
