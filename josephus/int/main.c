#include "josephus.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Needs at least an argument to create the list and the initial number");
        return 1;
    }
    if (argc > 4) {
        perror("Too many arguments!");
        return 1;
    }

    josephusList* josephus = init(atoi(argv[1]));

    run(josephus, atoi(argv[2]), argc > 3);

    printAll(josephus);

    destroy(josephus);
}
