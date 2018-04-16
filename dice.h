struct Dice {
    int value;
    int seed;
};

/* returns a number between 1 and num_sides (inclusive) as if rolling */
int roll(struct Dice dice1, int num_sides) {
    srand(time(NULL));
    return rand() % num_sides;
}
