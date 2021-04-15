#include <stdlib.h>
// #include <sys/time.h>
#include <time.h>
#include "../List with stack and queue/list.h"

#include "item.h"

#define CUTOFF (15)

// Just to copy from slide, won't use on this exercise
void shuffle(Item* a, int N) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand48(tv.tv_usec);
    for (int i = N - 1; i > 0; i--) {
        int j = (unsigned int)(drand48() * (i + 1));
        exch(a[i], a[j]);
    }
}

int randomBetween(int lo, int hi) {
    return lo + (rand() % (hi - lo + 1));
}

void insertionSort(Item* a, int lo, int hi) {
    for (int i = lo; i < hi; i++) {      // Para todos os elementos
        for (int j = i; j > lo; j--) {   // Para os ordenados
            compexch(a[j], a[j - 1]);
        }
    }
}


int median_of_3(Item* a, int lo, int hi) {
    // TODO srand only once
    // struct timeval tv;
    // gettimeofday(&tv, NULL);
    // srand48(tv.tv_usec);
    // time_t time(NULL);
    srand(time(0));

    int medianOf[3] = { randomBetween(lo, hi), randomBetween(lo, hi), randomBetween(lo, hi) };

    if (medianOf[0] <= medianOf[1]) {
        if (medianOf[1] <= medianOf[2]) return medianOf[1];
        return medianOf[2];
    } else {
        if (medianOf[1] <= medianOf[2]) return medianOf[0];
        return medianOf[1];
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

// Top-down, recursive
void quick_sort_recursive(Item* a, int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insertionSort(a, lo, hi);
        return;
    }
    int median = median_of_3(a, lo, hi);
    exch(a[lo], a[median]);
    int j = partition(a, lo, hi);
    quick_sort_recursive(a, lo, j - 1);
    quick_sort_recursive(a, j + 1, hi);
}

// Bottom-up, iterative

void mallocAndPush(list_t* list, int A) {
    int* m = malloc(sizeof(int));
    *m = A;
    list_push(list, m);
}

#define push2(L, A, B) mallocAndPush(L, B); mallocAndPush(L, A)

void quick_sort_iteractive(Item* a, int lo, int hi) {
    list_t* list = list_init();
    push2(list, lo, hi);
    while (!list_isEmpty(list)) {
        lo = *(int*)list_pop(list);
        hi = *(int*)list_pop(list);
        if (hi <= lo + CUTOFF - 1) {
            insertionSort(a, lo, hi);
            break;
        };
        int median = median_of_3(a, lo, hi);
        exch(a[lo], a[median]);
        int i = partition(a, lo, hi);
        if (i - lo > hi - i) {              // Test the size of sub-arrays.
            push2(list, lo, i - 1);         // Push the larger one.
            push2(list, i + 1, hi);         // Sort the smaller one first.
        } else {
            push2(list, i + 1, hi);
            push2(list, lo, i - 1);
        }
    }

    list_destroy(list);
}

void quick_sort_3way_recursive(Item* a, int lo, int hi) {
    // if (hi <= lo + CUTOFF - 1) {
    //     insertionSort(a, lo, hi);
    //     return;
    // }
    if (hi <= lo) return;
    Item v = a[lo];
    int lt = lo, gt = hi, i = lo;
    while (i <= gt) {
        if (a[i] < v) {
            exch(a[lt], a[i]);
            lt++;
            i++;
        } else if (a[i] > v) {
            exch(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }
    quick_sort_3way_recursive(a, lo, lt - 1);
    quick_sort_3way_recursive(a, gt + 1, hi);
}

void sort(Item* a, int lo, int hi) {
    // shuffle(a, hi - lo);
    quick_sort_3way_recursive(a, lo, hi);
}
