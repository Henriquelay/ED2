#include "item.h"

void sort(Item* a, int lo, int hi) {
    for (int i = lo; i < hi / 2; i++) {
        for (int j = lo + i; j < hi - i - 1; j++) {
            compexch(a[j + 1], a[j]);
        }
        for (int j = hi - i - 2; j > lo + i; j--) {
            compexch(a[j], a[j - 1]);
        }
    }
}
