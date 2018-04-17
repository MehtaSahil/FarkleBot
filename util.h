int has_one(int *counts) {
    return counts[0] >= 1;
}

int has_five(int *counts) {
    return counts[4] >= 1;
}

int has_triple(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] >= 3) {
            return 1;
        }
    }

    return 0;
}

int has_quad(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] >= 4) {
            return 1;
        }
    }

    return 0;
}

int has_quint(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] >= 5) {
            return 1;
        }
    }

    return 0;
}

int has_sextuple(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] >= 6) {
            return 1;
        }
    }

    return 0;
}

int has_straight(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] != 1) {
            return 0;
        }
    }

    return 1;
}

int has_three_pair(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {

        /* if the count is not zero, it must be 2 */
        if (counts[i] != 0) {
            if (counts[i] != 2) {
                return 0;
            }
        }
    }

    return 0;
}

int has_two_triple(int *counts, int length) {
    int i;
    for (i = 0; i < length; i++) {

        /* if the count is not zero, it must be 3 */
        if (counts[i] != 0) {
            if (counts[i] != 3) {
                return 0;
            }
        }
    }

    return 0;
}

int has_quad_pair(int *counts, int length) {
    int has_quad = 0;
    int has_pair = 0;

    int i;
    for (i = 0; i < length; i++) {
        if (counts[i] == 4) {
            has_quad = 1;
        }

        if (counts[i] == 2) {
            has_pair = 1;
        }
    }

    return has_quad && has_pair;
}

int is_scoring_roll(int *counts, int length) {
    if (has_one(counts)
        || has_five(counts)
        || has_triple(counts, length)
        || has_quad(counts, length)
        || has_quint(counts, length)
        || has_sextuple(counts, length)
        || has_straight(counts, length)
        || has_three_pair(counts, length)
        || has_quad_pair(counts, length)) {
        return 1;
    }

    return 0;
}
