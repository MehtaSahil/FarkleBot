#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dice.h"

#define NUM_SIDES 6

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int *counts = malloc(NUM_SIDES * sizeof(int));

    int i;
    for (i = 0; i < 10000000; i++) {
        int roll = rand() % 6;
        counts[roll] += 1;
    }

    i = 0;
    for (i = 0; i < NUM_SIDES; i++) {
        printf("%d : %d : %f\n", i, counts[i], ((float)counts[i])/10000000);
    }

    free(counts);
}
