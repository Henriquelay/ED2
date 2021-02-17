#include "stacks.h"
#include <string.h>

int main(int argc, char** argv) {
    stack_t* stackOP = NULL;    // Initializing with NULL marks that it
    stack_t* stackNUM = NULL;   // is not to be appended by later nodes

    for (int i = 1; i < argc; i++) {
        switch (argv[i][0]) {    // Only grabs first of arg
            case '(': break;    // Ignore
            case ')':           // Time to do some math
                ;   // Have to add an empty statement because, accordind to GCC:
                // "a label can only be part of a statement and a declaration is not a statement"
                // Even though a switch's case isn't __strictly__ a label I guess.
                // The same happens in cases after this one.
                // Oh well.
                double* result = (double*)malloc(sizeof(double));
                if (result == NULL) {
                    perror("Error allocating result variable. Exiting");
                    exit(1);
                }
                double* operand1 = pop(&stackNUM);
                double* operand2 = pop(&stackNUM);
                char* operation = pop(&stackOP);

                switch (*operation) {
                    case '+':
                        *result = *operand1 + *operand2;
                        break;
                    case '-':
                        *result = *operand1 - *operand2;
                        break;
                    case '*':
                        *result = *operand1 * *operand2;
                        break;
                    case '/':
                        *result = *operand1 / *operand2;
                        break;
                    default:
                        printf("Operation %c not recognized when searching for operators. Exiting\n", *operation);
                        exit(1);
                }
                free(operation);
                free(operand1);
                free(operand2);
                push(&stackNUM, result);
                break;

            case '+':
            case '-':
            case '*':
            case '/':;   // It's here again
                char* newOperation = (char*)malloc(sizeof(char));
                if (newOperation == NULL) {
                    perror("Error allocating operator char. Exiting");
                    exit(1);
                }
                *newOperation = argv[i][0];
                push(&stackOP, newOperation);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':;   // Also here
                double* num = (double*)malloc(sizeof(double));
                *num = strtod(argv[i], NULL);
                push(&stackNUM, num);
                break;
            default:
                printf("Operation %c not recognized. Exiting\n", argv[i][0]);
                exit(1);
        }
    }

    double* answer = pop(&stackNUM);

    printf("%.8f\n", *answer);

    free(answer);

    destroy(&stackOP);
    destroy(&stackNUM);

    return 0;
}
