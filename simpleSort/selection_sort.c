#include "item.h"

void sort(Item* a, int lo, int hi) {
    for (int i = lo; i < hi;i++) {      // For every element
        for (int j = i; j < hi; j++) {  // Search the ones later
            if (a[j] < a[i]) {         // If it's smaller than the first
                exch(a[j], a[i]);      // Swap them
            }
        }
    }
}
