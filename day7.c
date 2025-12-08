#include <stdio.h>

typedef struct Cell {
    enum {EMPTY, PATH, SPLIT} type;
    long paths;
} Cell;

int main() {
    FILE *fp = fopen("day7input.txt", "rb");
    int line_number = 0, num_splits = 0;
    char input[256]; 
    fgets(input, sizeof(input), fp);
    Cell diagram[256][256] = {0};
    diagram[0][70] = (Cell){.type=PATH};
    while(fgets(input, sizeof(input), fp)) { 
        for (int i = 0; i < 140; ++i) {
            if (diagram[line_number][i].type == PATH) {
                if (input[i] == '.') diagram[line_number+1][i] = (Cell){.type = PATH};
                if (input[i] == '^') {
                    diagram[line_number+1][i] = (Cell){.type = SPLIT};
                    diagram[line_number+1][i - 1] = (Cell){.type = PATH};
                    diagram[line_number+1][i + 1] = (Cell){.type = PATH};
                    num_splits++;
                }
            }
        }
        line_number++;
    }
    printf("Number of splits: %d\n", num_splits);

    // Part 2
    for (int i = 0; i<141; i++) { diagram[line_number][i].paths = 1; }
    for (int i=line_number-1; i>=0; i--) {
        for (int j=0; j<140; j++) {
            if (diagram[i][j].type == SPLIT) {
                diagram[i][j].paths = diagram[i+1][j-1].paths + diagram[i+1][j+1].paths;
            } else if (diagram[i][j].type == PATH) {
                diagram[i][j].paths = diagram[i+1][j].paths;
            }
        }
    }
    printf("Number of paths: %ld\n", diagram[0][70].paths);
}
