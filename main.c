#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dice.h"
#include "util.h"

#define NUM_SIDES 6
#define NUM_DICE 1

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int *counts = malloc(NUM_SIDES * sizeof(int));
    struct Die d1;
    struct Die d2;
    struct Die d3;
    struct Die d4;
    struct Die d5;
    struct Die d6;

    int total_rolls = 10000000;
    int total_scoring_rolls = 0;

    int i, j;
    for (i = 0; i < total_rolls; i++) {

        /* reset counts vector (new roll) */
        for (j = 0; j < NUM_SIDES; j++) {
            counts[j] = 0;
        }

        /* just roll one dice for now */
        int roll_val_1 = roll(d1, NUM_SIDES);
        int roll_val_2 = roll(d2, NUM_SIDES);
        int roll_val_3 = roll(d3, NUM_SIDES);
        int roll_val_4 = roll(d4, NUM_SIDES);
        int roll_val_5 = roll(d5, NUM_SIDES);
        int roll_val_6 = roll(d6, NUM_SIDES);
        counts[roll_val_1] += 1;
        counts[roll_val_2] += 1;
        counts[roll_val_3] += 1;
        counts[roll_val_4] += 1;
        counts[roll_val_5] += 1;
        /* counts[roll_val_6] += 1; */

        if (is_scoring_roll(counts, NUM_SIDES)) {
            total_scoring_rolls += 1;
        }
    }

    printf("total rolls: %d\n", total_rolls);
    printf("probability of scoring: %f\n", (float)(total_scoring_rolls) / total_rolls);

    free(counts);
}
