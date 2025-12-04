#include <stdio.h>
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

#define FOR_EACH_CELL_WITH_LT_4_NEIGHBORS(block) do {                          \
    for (int i = 1; i < HEIGHT + 1; i++) {                                     \
      for (int j = 1; j < LENGTH + 1; j++) {                                   \
        if (diagram[i][j] == 1 && count_neighbors(diagram, i, j) < 4) {        \
          block;                                                               \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  } while (0)

int main() {
    FILE *fp = fopen("day4input.txt", "rb");

    char diagram[HEIGHT+2][LENGTH+2] = {0}; // Border padding
    int line_number = 0;
    for (char input[256]; fgets(input, sizeof(input), fp);) {
        for (int i = 0; i < LENGTH; ++i) {
            if (input[i] == '@') diagram[(line_number + 1)][(i + 1)] = 1;
        }
        line_number++;
    }

    // Part 1
    int count = 0;
    FOR_EACH_CELL_WITH_LT_4_NEIGHBORS({count++;});
    printf("Count: %d\n", count);

    // Part 2
    int count_removed = 0;
    for (bool found = true; found;) {
        found = false;
        FOR_EACH_CELL_WITH_LT_4_NEIGHBORS({ found = true; count_removed++; diagram[i][j] = 0; });
    }
    printf("Count removed: %d\n", count_removed);
    return 0;
}
