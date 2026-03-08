#ifndef SORT_H
#define SORT_H

#include "nsort.h"

Metrics selection_sort(Column columns[], int size, int y, int fps);

Metrics bubble_sort(Column columns[], int size, int y, int fps);

Metrics insertion_sort(Column columns[], int size, int y, int fps);

void bogo_sort(Column columns[], int size, int y, int fps);

#endif
