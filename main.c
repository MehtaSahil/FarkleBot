#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int determine_action(int, int, char*);
int generate_sequences(int*, int, int*, int, int**, int*);
int print_zero_terminated_int_array(int*, int);
int print_int_array(int*, int, int);
int choose_dice(int*, int);

int main2(int argc, char *argv[]) {
    int still_playing = 1;
    int running_total = 0;
    int scored = 0;
    int remaining_dice = 6;
    char* action = malloc(50 * sizeof(char));

    while (still_playing) {

        printf("running total : %d\n", running_total);
        printf("remaining dice : %d\n", remaining_dice);

        printf("how much did you score? : ");
        scanf("%d", &scored);

        if (scored == 0) {
            printf("FARKLE\n");
            running_total = 0;
            break;
        } else {
            running_total += scored;
        }

        printf("how many dice are left? : ");
        scanf("%d", &remaining_dice);

        printf("\n");
        printf("Okay, your current total is %d.\n", running_total);

        determine_action(running_total, remaining_dice, action);
        printf("With %d dice remaining, I suggest that you [%s]\n", remaining_dice, action);

        printf("Would you like to continue? [Y = 1 / N = 0] : ");
        scanf("%d", &still_playing);
        printf("\n");
    }

    printf("You scored : %d\n", running_total);
    printf("Thank you for playing.\n");

    free(action);
}

int main(int argc, char* argv[]) {

    int* roll = malloc(6 * sizeof(int));
    roll[0] = 4;
    roll[1] = 3;
    roll[2] = 4;
    /* roll[3] = 2;
    roll[4] = 4;
    roll[5] = 6; */

    choose_dice(roll, 3);

    free(roll);

    return 0;
}

/* Given a set of values for rolled dice, choose the best dice
to keep before moving forward */
int choose_dice(int* roll, int num_rolled_dice) {

    printf("initial roll : ");
    print_int_array(roll, 0, num_rolled_dice-1);

    /* Generate all selections of dice */
    int* indices = malloc(num_rolled_dice * sizeof(int));
    int num_indices = num_rolled_dice;

    int i;
    for (i = 0; i < num_rolled_dice; i++) {
        indices[i] = i;
    }

    int sequence_length = 0;
    int* sequence = malloc(sequence_length * sizeof(int));
    int* num_sequences = malloc(sizeof(int));

    /* stores all sequences of selection indices
        e.g. [0, 2, 1] selects the 0th, 2nd, and 1st indices from the roll
        IN THAT ORDER */
    int** sequences = malloc(5000 * sizeof(int*));

    generate_sequences(indices, num_indices,
                        sequence, sequence_length,
                        sequences, num_sequences);

    /* make all selections */
    for (i = 0; i < *num_sequences; i++) {
        int* selection_indices = sequences[i];
        int selection_length = sequences[i][0];

        int* selection = malloc(selection_length * sizeof(int));

        int j;
        for (j = 0; j < selection_length; j++) {
            selection[j] = roll[selection_indices[j+1]];
        }

        print_int_array(selection, 0, selection_length - 1);

        /* for each selection:
            generate counts array
            use util.h functions to determine ways to score with the selection
            choose the max possible score for this selection
            pick the highest max score from all selections
            return this selection as the desired selection */

        free(selection);
    }

    /* cleanup */
    for (i = 0; i < *num_sequences; i++) {
        free(sequences[i]);
    }

    free(num_sequences);
    free(sequences);

    return 0;
}

int determine_action(int running_total, int remaining_dice, char* action) {
    float* running_total_limits = malloc(6 * sizeof(float));
    running_total_limits[5] = 12430.102;
    running_total_limits[4] = 1918.333;
    running_total_limits[3] = 610.049;
    running_total_limits[2] = 225.833;
    running_total_limits[1] = 93.75;
    running_total_limits[0] = 37.5;

    if (running_total > running_total_limits[remaining_dice - 1]) {
        strcpy(action, "stop");
    } else {
        strcpy(action, "continue");
    }

    free(running_total_limits);

    return 0;
}

int generate_sequences(int* arr, int arr_length,
                        int* sequence, int sequence_length,
                        int** sequences, int* sequence_count) {

    /* Base case */
    if (sequence_length == arr_length) {
        return 0;
    }

    int i, j;
    for (i = 0; i < arr_length; i++) {

        /* If arr[i] is already in the sequence, move to next index */
        int previously_contained = 0;
        for (j = 0; j < sequence_length; j++) {
            if (sequence[j] == arr[i]) {
                previously_contained = 1;
            }
        }

        if (previously_contained) {
            continue;
        }

        /* Copy old sequence into new sequence before appending */
        int new_sequence_length = sequence_length + 1;
        int* new_sequence = malloc(new_sequence_length * sizeof(int));

        for (j = 0; j < sequence_length; j++) {
            new_sequence[j] = sequence[j];
        }

        /* append new item to old sequence */
        new_sequence[new_sequence_length - 1] = arr[i];

        /* embed length of sequence as first element of the array
        This is NOT ideal. Implement sequences as int*** for cleaner impl
        */
        int* new_sequence_with_length = malloc((new_sequence_length+1) * sizeof(int));
        for (j = 0; j < new_sequence_length; j++) {
            new_sequence_with_length[j+1] = new_sequence[j];
        }

        new_sequence_with_length[0] = new_sequence_length;

        sequences[*sequence_count] = new_sequence_with_length;
        *sequence_count = *sequence_count + 1;

        generate_sequences(arr, arr_length,
                            new_sequence, new_sequence_length,
                            sequences, sequence_count);

        free(new_sequence);
    }
}

int print_int_array(int* arr, int start, int stop) {
    printf("[");

    int i;
    for (i = start; i < stop; i++) {
        printf("%d, ", arr[i]);
    }

    printf("%d]\n", arr[i]);
}
