#include "item.h"

// Just to copy from slide, won't use on this exercise
// void shuffle(Item* a, int N) {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     srand48(tv.tv_usec);
//     for (int i = N - 1; i > 0; i--) {
//         int j = (unsigned int)(drand48() * (i + 1));
//         exch(a[i], a[j]);
//     }
// }

int partition(Item* a, int lo, int hi) {
    int i = lo, j = hi + 1;
    Item v = a[lo];
    while (1) {
        while (less(a[++i], v)) // Find item on left to swap.
            if (i == hi) break;
        while (less(v, a[--j])) // Find item on right to swap.
            if (j == lo) break;
        if (i >= j) break;      // Check if pointers cross.
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]);          // Swap with partitioning item.
    return j;                   // Return index of item known to be in place.
}

void sort(Item* a, int lo, int hi) {
    if (hi <= lo) {
        return;
    }
    int j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}
