#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    unsigned int id;                  // identificador do nó
    unsigned int weight;     // valor associado ao nó
    struct Edge* to;     // valor associado ao nó destino
} Edge;

typedef struct PQ {
    Edge** pq;
    int* map;
    unsigned int size;
} PQ;

#define id(A)           (A->id)                           // retorna identificador do nó
#define value(A)        (A->weight)                       // retorna valor do nó
#define to(A)           (id(A->to))                       // retorna id do nó destino
#define more(A, B)      (value(A) > value(B))          // compara nós, por valor
// #define exch(A, B)      { Item t = A; A = B; B = t; }  // troca dois nós
void exch(Edge** a, Edge** b) {
    Edge* T = *a;
    *a = *b;
    *b = T;
}

Edge make_item(unsigned int id, unsigned int value, Edge* to) {
    Edge t;
    t.id = id;
    t.weight = value;
    t.to = to;
    return t;
}

void print_item(Edge* item) {
    if (item == NULL) { printf("NULL"); return; }
    printf("%u-", id(item));
    printf("%u", value(item));
    printf("->%u", to(item));
}

Edge* init_item(unsigned int id, unsigned int value, Edge* to) {
    Edge* newItem = (Edge*)malloc(sizeof(Edge));
    *newItem = make_item(id, value, to);
    return newItem;
}

void swap(PQ* pq, unsigned int i, unsigned int j) {
    exch(&pq->pq[i], &pq->pq[j]);
    // pq->map[id(pq->pq[i])] = i;
    // pq->map[id(pq->pq[j])] = j;
}

void fix_up(PQ* pq, unsigned int k) {
    while (k > 1 && more(pq->pq[k / 2], pq->pq[k])) {
        if (pq && pq->pq) {
        }
        swap(pq, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PQ* pq, unsigned int parent) {
    while (2 * parent <= pq->size) {
        unsigned int child = 2 * parent;
        // child < pq->size checks if there's a position after child, since PQ starts at 1;
        if (child < pq->size && more(pq->pq[child], pq->pq[child + 1])) {
            child++;
        }
        if (!more(pq->pq[parent], pq->pq[child])) {
            break;
        }
        swap(pq, parent, child);
        parent = child;
    }
}

PQ* PQ_init(unsigned int maxSize) {
    PQ* pq = (PQ*)malloc(sizeof(PQ));
    pq->pq = (Edge**)calloc(maxSize + 1, sizeof(Edge*));
    pq->map = (unsigned int*)malloc((maxSize + 1) * sizeof(unsigned int));
    pq->size = 0;
    return pq;
}

void PQ_print(PQ* pq) {
    if (pq == NULL) {
        puts("It's NULL");
        return;
    }
    printf("PQ=%p map=%p size=%u\n", (void*)pq->pq, (void*)pq->map, pq->size);
    // This implementation skips index 0
    for (unsigned int i = 0; i <= pq->size; i++) {
        printf("[%u] ", i);
        print_item(pq->pq[i]);
        printf("\n");
    }
}

// FIXME
void PQ_insert(PQ* pq, Edge* v) {
    pq->size++;
    pq->pq[pq->size] = v;
    pq->map[id(v)] = pq->size;
    fix_up(pq, pq->size);
}

Edge* PQ_min(PQ* pq) {
    return pq->pq[1];
}

Edge* PQ_delmin(PQ* pq) {
    Edge* min = PQ_min(pq);
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, 1);
    return min;
}

void PQ_decrease_key(PQ* pq, unsigned int id, unsigned int value) {
    unsigned int i = pq->map[id];
    value(pq->pq[i]) = value;
    fix_up(pq, i);
}

char PQ_empty(PQ* pq) {
    return pq->size == 0;
}

char PQ_exists(PQ* pq, unsigned int key) {
    for (unsigned int i = 1; i <= pq->size; i++) {
        if (id(pq->pq[i]) == key) return 1;
    }
    return 0;
}

char PQ_existsAddr(PQ* pq, void* keyAddr) {
    for (unsigned int i = 0; i < pq->size; i++) {
        if (&(pq->pq[i]) == keyAddr) return 1;
    }
    return 0;
}

unsigned int PQ_size(PQ* pq) {
    return pq->size;
}

// Frees the Items inside too
void PQ_finish(PQ* pq) {
    if (pq == NULL) return;
    for (unsigned int i = 0; i < pq->size;) {
        free(pq->pq[++i]);
    }
    free(pq->pq);
    free(pq->map);
    free(pq);
    pq = NULL;
}

/////////////////////////////////////

unsigned int* dijkstra(PQ** vertex, unsigned int nVert, int starting) {
    // If starting node has no edges
    // Will be useful quitting early to not allocate anything
    if (vertex[starting] == NULL) {
        return NULL;
    }

    // printf("Starts at: %u\n", starting);

    // Ditance array to keep track of distances from graph[starting] to graph[n]
    unsigned int* distances = malloc(sizeof * distances * nVert);
    // To mark visited nodes
    char visited[nVert];
    // Internal Dijkstra's control
    PQ* dijEdges = PQ_init(3000);

    // Initializing arrays
    for (unsigned int i = 1; i <= vertex[starting]->size; i++) {
        PQ_insert(dijEdges, vertex[starting]->pq[i]);
    }
    for (unsigned int i = 0; i < nVert; i++) {
        // I    nitializes with maximum distance, gets replaced on first iteration
        distances[i] = UINT_MAX;
        visited[i] = 0;

        // Inserting only starting node
        // Inserting all edges from every vertice
        // for (unsigned int j = 1; j <= vertex[i]->size; j++) {
        //     PQ_insert(dijVertex[i], vertex[i]->pq[j]);
        // }
    }
    // A vertice's distance to itself is 0.
    distances[starting] = 0;


    // puts("After starting everything:");
    // PQ_print(dijEdges);

    // TODO
    while (!PQ_empty(dijEdges)) {
        // puts("Current state:");
        // PQ_print(dijEdges);
        Edge* edge = PQ_delmin(dijEdges);
        // printf("Current edge:");
        // print_item(edge);
        // printf("\nDistances:[");
        // for (unsigned int k = 0; k < nVert; k++) {
        //     printf("%u ", distances[k]);
        // }
        // puts("]");
        unsigned int newDistance = distances[id(edge)] == UINT_MAX ? value(edge) : distances[id(edge)] + value(edge);

        // printf("NewDistance from %u to %u: %u\n", id(edge), to(edge), newDistance);
        if (newDistance < distances[to(edge)]) {
            // puts("Updating distance");
            distances[to(edge)] = newDistance;
            if (!visited[to(edge)]) {
                for (unsigned int j = 1; j <= vertex[starting]->size; j++) {
                    PQ_insert(dijEdges, vertex[to(edge)]->pq[j]);
                }
            }
        }

        visited[id(edge)] = 1;
        // puts("");
    }


    free(dijEdges->pq);
    free(dijEdges->map);
    free(dijEdges);
    return distances;
}

int main(int argc, char* argv[]) {
    unsigned int N;
    scanf("%u", &N);

    for (unsigned int i = 0; i < N; i++) {
        printf("Case #%u: ", i + 1);
        // puts("");

        unsigned int n, m, S, T;
        scanf("%u %u %u %u", &n, &m, &S, &T);

        // printf("n=%u m=%u S=%u T=%u\n", n, m, S, T);

        PQ* pqMap[n];
        for (unsigned int j = 0; j < n; j++) {
            pqMap[j] = NULL;
        }
        // PQ for edges on each server
        for (unsigned int j = 0; j < m; j++) {
            unsigned int Scur, Tcur, w;
            scanf("%u %u %u", &Scur, &Tcur, &w);
            // printf("s=%u t=%u w=%u\n", Scur, Tcur, w);

            // TODO make increasing-size PQ if filled
            if (pqMap[Scur] == NULL) pqMap[Scur] = PQ_init(1000);
            if (pqMap[Tcur] == NULL) pqMap[Tcur] = PQ_init(1000);

            Edge* SItem = init_item(Scur, w, NULL);
            Edge* TItem = init_item(Tcur, w, SItem);
            SItem->to = TItem;

            PQ_insert(pqMap[Scur], SItem);
            PQ_insert(pqMap[Tcur], TItem);
        }

        /// OK

        // for (unsigned int j = 0; j < n; j++) {
        //     printf("pqMap[%u] AFTER parsing:\n(", j);
        //     PQ_print(pqMap[j]);
        //     puts(")");
        // }

        // printf("\nDoing dijkstra from %u to %u\n", S, T);
        unsigned int* distances = dijkstra(pqMap, n, S);
        // Printing distances
        // printf("Distances:\n[");
        // if (distances != NULL) {
        //     for (unsigned int k = 0; k < n; k++) {
        //         printf("%u ", distances[k]);
        //     }
        // } else {
        //     printf("NULL");
        // }
        // printf("]\n");

        if (distances != NULL) {
            printf("%u", distances[T]);
        } else {
            printf("unreachable");
        }
        puts("");


        free(distances);
        for (unsigned int j = 0; j < n; j++) {
            PQ_finish(pqMap[j]);
        }
        // puts("-----------");
    }

    return 0;
}
