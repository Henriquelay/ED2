#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Fazer lista de aresta ao inves de array -- para manter quantas quisermos */
typedef struct Item_Edge {
    unsigned int id;          /* identificador do nó */
    unsigned int weight;     /* valor associado ao nó */
    unsigned int to;     /* valor associado ao nó destino */
} Item_Edge;

typedef struct PQ_Vertex {
    Item_Edge** edges;
    unsigned int* map;
    unsigned int size;
} PQ_Vertex;

#define id(A)           (A->id)                           /* retorna identificador do nó */
#define value(A)        (A->weight)                       /* retorna valor do nó */
#define to(A)           (A->to)                       /* retorna id do nó destino */
#define more(A, B)      (value(A) > value(B))          /* compara nós, por valor */
/* #define exch(A, B)      { Item t = A; A = B; B = t; }  // troca dois nós */
void exch(Item_Edge** a, Item_Edge** b) {
    Item_Edge* T = *a;
    *a = *b;
    *b = T;
}

Item_Edge make_item(unsigned int id, unsigned int value, unsigned int to) {
    Item_Edge t;
    t.id = id;
    t.weight = value;
    t.to = to;
    return t;
}

void print_item(Item_Edge* item) {
    if (item == NULL) { printf("NULL"); return; }
    printf("%u-", id(item));
    printf("%u", value(item));
    printf("->%u", to(item));
}

Item_Edge* init_item(unsigned int id, unsigned int value, unsigned int to) {
    Item_Edge* newItem = malloc(sizeof * newItem);
    *newItem = make_item(id, value, to);
    return newItem;
}

void swap(PQ_Vertex* pq, unsigned int i, unsigned int j) {
    exch(&pq->edges[i], &pq->edges[j]);
    pq->map[id(pq->edges[i])] = i;
    pq->map[id(pq->edges[j])] = j;
}

void fix_up(PQ_Vertex* pq, unsigned int k) {
    while (k > 1 && more(pq->edges[k / 2], pq->edges[k])) {
        if (pq && pq->edges) {
        }
        swap(pq, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PQ_Vertex* pq, unsigned int parent) {
    while (2 * parent <= pq->size) {
        unsigned int child = 2 * parent;
        /* child < pq->size checks if there's a position after child, since PQ starts at 1; */
        if (child < pq->size && more(pq->edges[child], pq->edges[child + 1])) {
            child++;
        }
        if (!more(pq->edges[parent], pq->edges[child])) {
            break;
        }
        swap(pq, parent, child);
        parent = child;
    }
}

PQ_Vertex* PQ_init(unsigned int maxSize) {
    PQ_Vertex* pq = malloc(sizeof * pq);
    pq->edges = malloc(sizeof * pq->edges * (maxSize + 1));
    pq->map = malloc(sizeof * pq->map * (maxSize + 1));
    pq->size = 0;
    return pq;
}

void PQ_print(PQ_Vertex* pq) {
    if (pq == NULL) {
        puts("It's NULL");
        return;
    }
    printf("PQ=%p map=%p size=%u\n", (void*)pq->edges, (void*)pq->map, pq->size);
    /* This implementation skips index 0 */
    unsigned int i;
    for (i = 0; i <= pq->size; i++) {
        printf("[%u] ", i);
        print_item(pq->edges[i]);
        printf("\n");
    }
}

void PQ_insert(PQ_Vertex* pq, Item_Edge* v) {
    pq->size++;
    pq->edges[pq->size] = v;
    pq->map[id(v)] = pq->size;
    fix_up(pq, pq->size);
}

Item_Edge* PQ_min(PQ_Vertex* pq) {
    return pq->edges[1];
}

Item_Edge* PQ_delmin(PQ_Vertex* pq) {
    Item_Edge* min = PQ_min(pq);
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, 1);
    return min;
}

void PQ_decrease_key(PQ_Vertex* pq, unsigned int id, unsigned int value) {
    unsigned int i = pq->map[id];
    /* Decreasing priority is increasing key in a ascending PQ */
    value(pq->edges[i]) = value;
    fix_up(pq, i);
}

char PQ_empty(PQ_Vertex* pq) {
    return pq->size == 0;
}

char PQ_exists(PQ_Vertex* pq, unsigned int key) {
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        if (id(pq->edges[i]) == key) return 1;
    }
    return 0;
}

char PQ_existsAddr(PQ_Vertex* pq, void* keyAddr) {
    unsigned int i;
    for (i = 0; i < pq->size; i++) {
        if (&(pq->edges[i]) == keyAddr) return 1;
    }
    return 0;
}

unsigned int PQ_size(PQ_Vertex* pq) {
    return pq->size;
}

/* Frees the Items inside too */
void PQ_finish(PQ_Vertex* pq) {
    if (pq == NULL) return;
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        free(pq->edges[i]);
    }
    free(pq->edges);
    free(pq->map);
    free(pq);
    pq = NULL;
}

/*/////////////////////////////////// */

unsigned int* dijkstra(PQ_Vertex** vertex, unsigned int nVert, int starting) {
    /* If starting node has no edges */
    /* Will be useful quitting early to not allocate anything */
    if (vertex[starting] == NULL) {
        return NULL;
    }

    /* printf("Starts at: %u\n", starting); */

    /* Ditance array to keep track of distances from graph[starting] to graph[n] */
    unsigned int* distances = malloc(sizeof * distances * nVert);
    /* To mark visited nodes */
    /* char visited[nVert]; */
    /* Internal Dijkstra's control */
    PQ_Vertex* dijEdges = PQ_init(3000);

    /* for (i = 1; i <= vertex[starting]->size; i++) {
        PQ_insert(dijEdges, vertex[starting]->edges[i]);
    } */
    unsigned int i;
    /* Inserting only starting node */
    for (i = 0; i < nVert; i++) {
        /* I    nitializes with maximum distance, gets replaced on first iteration */
        distances[i] = UINT_MAX;
        /* visited[i] = 0; */

        /* Inserting all edges from every vertice */
        unsigned int j;
        for (j = 1; j <= vertex[i]->size; j++) {
            PQ_insert(dijEdges, vertex[i]->edges[j]);
        }
    }
    /* A vertice's distance to itself is 0. */
    distances[starting] = 0;


    /* puts("\nAfter starting everything, before dijkstra:");
    PQ_print(dijEdges); */

    while (!PQ_empty(dijEdges)) {
        /* puts("Current state:");
        PQ_print(dijEdges); */
        Item_Edge* edge = PQ_delmin(dijEdges);
        /* puts("After delmin:");
        PQ_print(dijEdges);
        printf("Current edge:");
        print_item(edge);
        printf("\nDistances:[");
        unsigned int k;
        for (k = 0; k < nVert; k++) {
            printf("%u ", distances[k]);
        }
        puts("]"); */
        unsigned int newDistance = distances[id(edge)] + value(edge);
        /* printf("NewDistance from starting to %u: %u\n", to(edge),  newDistance); */

        if (newDistance < distances[to(edge)]) {
            /* puts("Updating distance"); */
            distances[to(edge)] = newDistance;
            /* PQ_decrease_key(dijEdges, to(edge), newDistance); */
        }
        /* printf("NewDistances:[");
        for (k = 0; k < nVert; k++) {
            printf("%u ", distances[k]);
        }
        puts("]"); */

        /* visited[id(edge)] = 1; */
        /* puts(""); */
    }


    free(dijEdges->edges);
    free(dijEdges->map);
    free(dijEdges);
    return distances;
}

int main(int argc, char* argv[]) {
    unsigned int N;
    scanf("%u", &N);

    unsigned int i;

    for (i = 0; i < N; i++) {
        printf("Case #%u: ", i + 1);
        /* puts(""); */

        unsigned int n, m, S, T;
        scanf("%u %u %u %u", &n, &m, &S, &T);

        /* printf("n=%u m=%u S=%u T=%u\n", n, m, S, T); */

        PQ_Vertex* pqMap[n];
        unsigned int j;
        for (j = 0; j < n; j++) {
            pqMap[j] = NULL;
        }
        /* PQ for edges on each server */
        for (j = 0; j < m; j++) {
            unsigned int Scur, Tcur, w;
            scanf("%u %u %u", &Scur, &Tcur, &w);
            /* printf("s=%u t=%u w=%u\n", Scur, Tcur, w); */

            /* TODO make increasing-size PQ if filled */
            if (pqMap[Scur] == NULL) pqMap[Scur] = PQ_init(1000);
            if (pqMap[Tcur] == NULL) pqMap[Tcur] = PQ_init(1000);

            Item_Edge* SItem = init_item(Scur, w, Tcur);
            Item_Edge* TItem = init_item(Tcur, w, Scur);

            PQ_insert(pqMap[Scur], SItem);
            PQ_insert(pqMap[Tcur], TItem);
        }

        /*/ OK */

        /* unsigned int j; for (j = 0; j < n; j++) { */
        /*     printf("pqMap[%u] AFTER parsing:\n(", j); */
        /*     PQ_print(pqMap[j]); */
        /*     puts(")"); */
        /* } */

        /* printf("\nDoing dijkstra from %u to %u\n", S, T); */
        unsigned int* distances = dijkstra(pqMap, n, S);
        /* Printing distances */
        /* printf("Distances:\n["); */
        /* if (distances != NULL) { */
        /*     unsigned int k;     for (k = 0; k < n; k++) { */
        /*         printf("%u ", distances[k]); */
        /*     } */
        /* } else { */
        /*     printf("NULL"); */
        /* } */
        /* printf("]\n"); */

        if (distances == NULL || distances[T] == UINT_MAX) {
            printf("unreachable");
        } else {
            printf("%u", distances[T]);
        }
        puts("");


        free(distances);
        for (j = 0; j < n; j++) {
            PQ_finish(pqMap[j]);
        }
        /* puts("-----------"); */
    }

    return 0;
}
