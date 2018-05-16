#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int determine_action(int, int, char*);
int generate_sequences(int*, int, int*, int, int**, int*);
int print_zero_terminated_int_array(int*, int);
int print_int_array(int*, int, int);

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

int main(int argc, char *argv[]) {
    int i;

    int arr_length = 3;
    int* arr = malloc(arr_length * sizeof(int));

    for (i = 0; i < arr_length; i++) {
        arr[i] = i+1;
    }

    int sequence_length = 0;
    int* sequence = malloc(sequence_length * sizeof(int));
    int* sequence_count = malloc(sizeof(int));

    /* TODO : make allocation more specific to arr_length
    num_sequences = n + n(n-1) + n(n-1)(n-2) + ... + n! */
    int** sequences = malloc(5000 * sizeof(int*));

    generate_sequences(arr, arr_length,
                        sequence, sequence_length,
                        sequences, sequence_count);
    printf("%d\n", *sequence_count);

    /* print all generated sequences */
    for (i = 0; i < *sequence_count; i++) {
        /* print starting at 1 b/c [0] is length */
        print_int_array(sequences[i], 1, sequences[i][0]);
    }

    /* cleanup */
    for (i = 0; i < *sequence_count; i++) {
        free(sequences[i]);
    }

    free(sequence_count);
    free(sequences);
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
