#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define EDGESIZE (500)

/* Fazer lista de aresta ao inves de array -- para manter quantas quisermos */
typedef struct Item_Vertex {
    unsigned int id;
    /* TODO - make it a dynamic list */
    unsigned int weight[EDGESIZE];
    unsigned int to[EDGESIZE];
    unsigned int size;
    unsigned int dist;
} Item_Vertex;

typedef struct PQ {
    unsigned int size;
    Item_Vertex** vertex;
    unsigned int* map;
} PQ;

#define id(A)           (A->id)                           /* retorna identificador do nó */
#define value(A)        (A->dist)                       /* retorna valor do nó */
#define to(A)           (A->to)                       /* retorna id do nó destino */
#define more(A, B)      (value(A) > value(B))          /* compara nós, por valor */
/* #define exch(A, B)      { Item t = A; A = B; B = t; }  // troca dois nós */
void exch(Item_Vertex** a, Item_Vertex** b) {
    Item_Vertex* T = *a;
    *a = *b;
    *b = T;
}

Item_Vertex make_item(unsigned int id) {
    Item_Vertex t;
    t.id = id;
    t.size = 0;
    unsigned int i;
    for (i = 0; i < EDGESIZE; i++) {
        t.to[i] = UINT_MAX;
        t.weight[i] = UINT_MAX;
    }
    t.dist = UINT_MAX;
    return t;
}

void print_item(Item_Vertex* item) {
    if (!item) { printf("NULL\n"); return; }
    printf("[Vertex %u] dist = (%u)\n", id(item), value(item));
    unsigned int i;
    for (i = 0; i < item->size; i++) {
        printf("%u--", id(item));
        printf("%u", item->weight[i]);
        printf("->%u\n", to(item)[i]);
    }
}

Item_Vertex* init_item(unsigned int id) {
    Item_Vertex* newItem = malloc(sizeof * newItem);
    *newItem = make_item(id);
    return newItem;
}

void swap(PQ* pq, unsigned int i, unsigned int j) {
    exch(&pq->vertex[i], &pq->vertex[j]);
    pq->map[id(pq->vertex[i])] = i;
    pq->map[id(pq->vertex[j])] = j;
}

void fix_up(PQ* pq, unsigned int k) {
    while (k > 1 && more(pq->vertex[k / 2], pq->vertex[k])) {
        swap(pq, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PQ* pq, unsigned int parent) {
    while (2 * parent <= pq->size) {
        unsigned int child = 2 * parent;
        /* child < pq->size checks if there's a position after child, since PQ starts at 1; */
        if (child < pq->size && more(pq->vertex[child], pq->vertex[child + 1])) {
            child++;
        }
        if (!more(pq->vertex[parent], pq->vertex[child])) {
            break;
        }
        swap(pq, parent, child);
        parent = child;
    }
}

PQ* PQ_init(unsigned int maxSize) {
    PQ* pq = malloc(sizeof * pq);
    pq->vertex = malloc(sizeof * pq->vertex * (maxSize + 1));
    pq->vertex[0] = NULL;
    pq->map = malloc(sizeof * pq->map * (maxSize + 1));
    pq->size = 0;
    return pq;
}

void PQ_print(PQ* pq) {
    if (pq == NULL) {
        puts("It's NULL");
        return;
    }
    printf("PQ=%p map=%p size=%u\n", (void*)pq->vertex, (void*)pq->map, pq->size);
    /* This implementation skips index 0 */
    unsigned int i;
    for (i = 0; i <= pq->size; i++) {
        printf("[%u] ", i);
        print_item(pq->vertex[i]);
    }
}

void PQ_insert(PQ* pq, Item_Vertex* v) {
    pq->size++;
    pq->vertex[pq->size] = v;
    pq->map[id(v)] = pq->size;
    fix_up(pq, pq->size);
}

Item_Vertex* PQ_min(PQ* pq) {
    return pq->vertex[1];
}

Item_Vertex* PQ_delmin(PQ* pq) {
    Item_Vertex* min = PQ_min(pq);
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, 1);
    return min;
}

void PQ_decrease_key(PQ* pq, unsigned int id, unsigned int value) {
    unsigned int i = pq->map[id];
    value(pq->vertex[i]) = value;
    /* printf("Novo valor %u\n", value(pq->vertex[i])); */
    fix_up(pq, i);
}

char PQ_empty(PQ* pq) {
    return pq->size == 0;
}

char PQ_exists(PQ* pq, unsigned int key) {
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        if (id(pq->vertex[i]) == key) return 1;
    }
    return 0;
}

char PQ_existsAddr(PQ* pq, void* keyAddr) {
    unsigned int i;
    for (i = 0; i < pq->size; i++) {
        if (&(pq->vertex[i]) == keyAddr) return 1;
    }
    return 0;
}

unsigned int PQ_size(PQ* pq) {
    return pq->size;
}

/* Frees the Items inside too */
void PQ_finish(PQ* pq) {
    if (pq == NULL) return;
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        free(pq->vertex[i]);
    }
    free(pq->vertex);
    free(pq->map);
    free(pq);
    pq = NULL;
}

/*/////////////////////////////////// */

void dijkstra(Item_Vertex* startingVertex[], unsigned int nVert, unsigned int starting, unsigned int target) {
    /* If starting node has no edges */
    /* Will be useful quitting early to not allocate anything */
    if (!startingVertex[starting]) {
        return;
    }
    startingVertex[starting]->dist = 0;
    if(starting == target) {
        return;
    }

    /* printf("Starts at: %u\n", starting); */

    /* Ditance array to keep track of distances from graph[starting] to graph[n] */
    /* unsigned int* distances = malloc(sizeof * distances * nVert); */
    /* To mark visited nodes */
    /* char visited[nVert]; */
    /* Internal Dijkstra's control */
    PQ* dijVertex = PQ_init(EDGESIZE);

    /* Inserting all vertices */
    unsigned int i;
    for (i = 0; i < nVert; i++) {
        PQ_insert(dijVertex, startingVertex[i]);
    }
    /* Inserting only starting node */
    /* for (i = 0; i < nVert; i++) {
        /* Initializes with maximum distance, gets replaced on first iteration 

        distances[i] = UINT_MAX;
        visited[i] = 0;
    } */
    /* A vertice's distance to itself is 0. */
    /* distances[starting] = 0; */



    /* puts("\nAfter starting everything, before dijkstra:");
    PQ_print(dijEdges); */

    while (!PQ_empty(dijVertex)) {
        /* puts("Current state:");
        PQ_print(dijVertex); */
        Item_Vertex* vertex = PQ_delmin(dijVertex);
        /* puts("After delmin:");
        PQ_print(dijVertex);
        printf("Current:");
        print_item(vertex);
        printf("\nDistances:[");
        unsigned int k;
        for (k = 0; k < nVert; k++) {
            printf("%u ", value(startingVertex[k]));
        }
        puts("]"); */
        for (i = 0; i < vertex->size; i++) {
            unsigned int distance = value(vertex) + vertex->weight[i];
            /* printf("Distance from %u to %u (%u) + (%u) = %u\n", id(vertex), to(vertex)[i], value(vertex), vertex->weight[i], distance); */
            if (distance < value(dijVertex->vertex[dijVertex->map[to(vertex)[i]]])) {
                /* puts("Updating distance"); */
                PQ_decrease_key(dijVertex, to(vertex)[i], distance);
            }
        }
        /* unsigned int k; */
        /* printf("NewDistances:[");
        for (k = 0; k < nVert; k++) {
            printf("%u ", value(startingVertex[k]));
        }
        puts("]"); */

        /* visited[id(edge)] = 1; */
        /* puts(""); */
    }


    free(dijVertex->vertex);
    free(dijVertex->map);
    free(dijVertex);
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

        Item_Vertex* vertices[n];
        unsigned int j;
        for (j = 0; j < n; j++) {
            vertices[j] = init_item(j);
        }
        /* PQ for edges on each server */
        for (j = 0; j < m; j++) {
            unsigned int Scur, Tcur, w;
            scanf("%u %u %u", &Scur, &Tcur, &w);
            /* printf("s=%u t=%u w=%u\n", Scur, Tcur, w); */

            /* printf("vertices[Scur] = %p\n", vertices[Scur]);
            printf("vertices[Scur]->size = %u\n", vertices[Scur]->size);
            printf("vertices[Scur]->to[vertices[Scur]->size] = %u\n", vertices[Scur]->to[vertices[Scur]->size]); */
            vertices[Scur]->to[vertices[Scur]->size] = Tcur;
            vertices[Tcur]->to[vertices[Tcur]->size] = Scur;
            vertices[Scur]->weight[vertices[Scur]->size++] = w;
            vertices[Tcur]->weight[vertices[Tcur]->size++] = w;
        }

        /*/ OK */

        /* puts("AFTER parsing:");
        PQ_print(vertices); */

        /* printf("\nDoing dijkstra from %u to %u\n", S, T); */
        dijkstra(vertices, n, S, T);
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

        if (vertices[T] == NULL || value(vertices[T]) == UINT_MAX) {
            printf("unreachable");
        } else {
            printf("%u", value(vertices[T]));
        }
        puts("");


        for (j = 0; j < n; j++) {
            free(vertices[j]);
        }
        /* puts("-----------"); */
    }

    return 0;
}
