#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long solve(char *input, int bat_size) {
    char *bat = calloc(bat_size + 1, 1);
    int l = strlen(input);
    int max_idx = -1;
    for (int k = bat_size; k > 0; k--) {
        for (int i = max_idx + 1; i < l - k; ++i) {
            if (input[i] > bat[bat_size - k]) {
                bat[bat_size - k] = input[i];
                max_idx = i;
            }
        }
    }
    return atol(bat);
}

int main() {
    FILE *fp = fopen("day3input.txt", "rb");

    char input[1024];
    long total_1 = 0, total_2 = 0;
    while (fgets(input, sizeof(input), fp)) {
        // Part 1
        total_1 += solve(input, 2);

        // Part 2
        total_2 += solve(input, 12);
    }

    printf("Total 1 joltage: %ld\n", total_1);
    printf("Total 2 joltage: %ld\n", total_2);
    return 0;
}
