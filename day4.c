#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HEIGHT 137
#define LENGTH 137

int count_neighbors(char diagram[HEIGHT+2][LENGTH+2], int i, int j) {
    int num_neighbors = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            if (diagram[i + di][j + dj] == 1) num_neighbors++;
        }
    }
    return num_neighbors;
}

int main() {
    FILE *fp = fopen("day4input.txt", "rb");

    char diagram[HEIGHT+2][LENGTH+2] = {0}; // Border padding
    int line_number = 0;
    char input[256];
    while (fgets(input, sizeof(input), fp)) {
        for (int i = 0; i < HEIGHT; ++i) {
            if (input[i] == '@') diagram[(line_number + 1)][(i + 1)] = 1;
        }
        line_number++;
    }

    // Part 1
    int count = 0;
    for (int i = 1; i < HEIGHT + 1; i++) {
        for (int j = 1; j < LENGTH + 1; j++) {
            if (diagram[i][j] == 0) continue;
            if (count_neighbors(diagram, i, j) < 4) count++;
        }
    }

    printf("Count: %d\n", count);

    // Part 2
    bool found = true;
    int count_removed = 0;
    while(found) {
        found = false;
        for (int i = 1; i < HEIGHT + 1 ; i++) {
            for (int j = 1; j < LENGTH + 1 ; j++) {
                if (diagram[i][j] == 0) continue;
                if (count_neighbors(diagram, i, j) < 4) {
                    found = true;
                    count_removed++;
                    diagram[i][j] = 0;
                }
            }
        }
    }
    printf("Count removed: %d\n", count_removed);
    return 0;
}
