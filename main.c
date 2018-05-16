#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int continue_or_stop(int, int, char*);

int main(int argc, char *argv[]) {
    int still_playing = 1;
    int running_total = 0;
    int scored = 0;
    int remaining_dice = 6;
    char* action = malloc(50 * sizeof(char));

    /* main game loop */
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

        continue_or_stop(running_total, remaining_dice, action);
        printf("With %d dice remaining, I suggest that you [%s]\n", remaining_dice, action);

        printf("Would you like to continue? [Y = 1 / N = 0] : ");
        scanf("%d", &still_playing);
        printf("\n");
    }

    printf("You scored : %d\n", running_total);
    printf("Thank you for playing.\n");

    free(action);
}

/* given the running total and the amount of dice left to roll
    decide (based on expected values) whether the player should roll again */
int continue_or_stop(int running_total, int remaining_dice, char* action) {
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
