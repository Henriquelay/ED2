#include "item.h"

void sort(Item* a, int lo, int hi) {
    for (int i = lo; i < hi; i++) {      // Para todos os elementos
        for (int j = i; j > lo; j--) {   // Para os ordenados
            compexch(a[j], a[j - 1]);
        }
    }
}
