#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("day7input.txt", "rb");

    int line_number = 0;
    char input[256]; 
    fgets(input, sizeof(input), fp);

    int previous_line[140] = {0};
    previous_line[70] = 1;
    int num_splits = 0;
    for (; fgets(input, sizeof(input), fp);) { 
        int next_line[140] = {0};
        for (int i = 0; i < 140; ++i) {
            if (previous_line[i] == 1) {
                if (input[i] == '.') next_line[i] = 1;
                if (input[i] == '^') {
                    next_line[i - 1] = 1;
                    next_line[i + 1] = 1;
                    num_splits++;
                }
            }
        }
        for (int i = 0; i < 140; ++i) {
            previous_line[i] = next_line[i];
        }
        line_number++;
    }
    printf("Number of splits: %d\n", num_splits);
}
