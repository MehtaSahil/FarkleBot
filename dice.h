struct Die {
    int value;
};

/* returns a number between 1 and num_sides (inclusive) as if rolling */
int roll(struct Die dice, int num_sides) {
    dice.value = rand() % num_sides;
    return dice.value;
}
