#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("day7input.txt", "rb");

    int line_number = 0, num_splits = 0;
    char input[256]; 
    fgets(input, sizeof(input), fp);

    int diagram[256][256] = {0};
    diagram[0][70] = 1;
    while(fgets(input, sizeof(input), fp)) { 
        for (int i = 0; i < 140; ++i) {
            if (diagram[line_number][i] == 1) {
                if (input[i] == '.') diagram[line_number+1][i] = 1;
                if (input[i] == '^') {
                    diagram[line_number+1][i - 1] = 1;
                    diagram[line_number+1][i + 1] = 1;
                    num_splits++;
                }
            }
        }
        line_number++;
    }
    printf("Number of splits: %d\n", num_splits);
}
