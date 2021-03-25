#include "item.h"

#define CUTOFF (15)

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

void insertionSort(Item* a, int lo, int hi) {
    for (int i = lo; i < hi; i++) {      // Para todos os elementos
        for (int j = i; j > lo; j--) {   // Para os ordenados
            compexch(a[j], a[j - 1]);
        }
    }
}

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
    if (hi <= lo + CUTOFF - 1) {
        insertionSort(a, lo, hi);
        return;
    }
    int j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}