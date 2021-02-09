#ifndef _SIEVE_H_
#define _SIEVE_H_

typedef struct node {
    unsigned char mark;
} t_list;

// Initialize the list with size N-1 (2 to N)
t_list* init(int size);

int indexFirstNotMarkedBigger(t_list* list, int biggerThan, int size);

void markAllMultiples(t_list* list, int multipleOf, int size);

void markEveryMultiple(t_list* list, int size);

void printPrimes(t_list* list, int size);

void destroy(t_list* list);

#endif
