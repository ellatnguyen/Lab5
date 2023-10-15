#include <stdio.h>
#include <stdlib.h>

// Template for Printing Combinations
void print_combinations(int td_twopt, int td_fg, int td, int threept, int safety) {
    printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td_twopt, td_fg, td, threept, safety);
}

// Adds Combinations
void add_combination(int combinations[][5], int* num_combinations, int td_twopt, int td_fg, int td, int threept, int safety) {
    for (int i = 0; i < *num_combinations; i++) {
        if (combinations[i][0] == td_twopt && combinations[i][1] == td_fg && combinations[i][2] == td && combinations[i][3] == threept && combinations[i][4] == safety) {
            return;
        }
    }
    combinations[*num_combinations][0] = td_twopt;
    combinations[*num_combinations][1] = td_fg;
    combinations[*num_combinations][2] = td;
    combinations[*num_combinations][3] = threept;
    combinations[*num_combinations][4] = safety;
    (*num_combinations)++;
}

// Finds Combinations
void find_combinations(int score, int current_score, int td_twopt, int td_fg, int td, int threept, int safety,
                      int combinations[][5], int* num_combinations) {
    if (current_score == score) {
        add_combination(combinations, num_combinations, td_twopt, td_fg, td, threept, safety);
        return;
    }

    if (current_score + 2 <= score) {
        find_combinations(score, current_score + 2, td_twopt, td_fg, td, threept, safety + 1, combinations, num_combinations);
    }
    if (current_score + 3 <= score) {
        find_combinations(score, current_score + 3, td_twopt, td_fg, td, threept + 1, safety, combinations, num_combinations);
    }
    if (current_score + 6 <= score) {
        find_combinations(score, current_score + 6, td_twopt, td_fg, td + 1, threept, safety, combinations, num_combinations);
    }
    if (current_score + 7 <= score) {
        find_combinations(score, current_score + 7, td_twopt, td_fg + 1, td, threept, safety, combinations, num_combinations);
    }
    if (current_score + 8 <= score) {
        find_combinations(score, current_score + 8, td_twopt + 1, td_fg, td, threept, safety, combinations, num_combinations);
    }
}

// Orders Combinations by Ascending Order
int compare_combinations(const void *a, const void *b) {
    int *combination1 = (int *)a;
    int *combination2 = (int *)b;

    // Compare Based on Priority: TD + 2pt, TD + FG, TD, 3pt FG, Safety
    if (combination1[0] != combination2[0]) {
        return combination1[0] - combination2[0];
    } else if (combination1[1] != combination2[1]) {
        return combination1[1] - combination2[1];
    } else if (combination1[2] != combination2[2]) {
        return combination1[2] - combination2[2];
    } else if (combination1[3] != combination2[3]) {
        return combination1[3] - combination2[3];
    } else {
        return combination1[4] - combination2[4];
    }
}

int main() {
    int score;

    while (1) {
        printf("Enter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score <= 1) {
            break;
        }

        printf("Possible combinations of scoring plays:\n");

        int combinations[100][5];
        int num_combinations = 0;

        find_combinations(score, 0, 0, 0, 0, 0, 0, combinations, &num_combinations);

        qsort(combinations, num_combinations, sizeof(int[5]), compare_combinations);

        for (int i = 0; i < num_combinations; i++) {
            print_combinations(combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], combinations[i][4]);
        }
    }

    return 0;
}
