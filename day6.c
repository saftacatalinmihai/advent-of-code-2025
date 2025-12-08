#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("day6input.txt", "rb");
    int nums[6][4 * 1024] = {0}, line_number = 0;
    long grand_total = 0, grand_total_2 = 0;
    char lines[4][4 * 1024] = {0};
    for (char input[4 * 1024]; fgets(input, sizeof(input), fp);) { 
        if (line_number < 4) strcpy(lines[line_number], input);
        int num = 0, offset = 0, chars_read = 0, column_number = 0;
        if (strchr(input, '+') != NULL) {
            char op;
            for (int count_read = sscanf(&input[offset], "%c%n", &op, &chars_read); count_read != EOF; count_read = sscanf(&input[offset], "%c%n", &op, &chars_read)) {
                int vertical_nums[4] = {0};
                switch (op) {
                    case '+':
                    case '*': {
                        int n = 0, vertical_block_len = 0;
                        for (int k = 0; k < 4; ++k) {
                            int bl;
                            sscanf(&lines[k][offset], "%d%n", &n, &bl);
                            if (bl > vertical_block_len) { vertical_block_len = bl; }
                        }
                        char numStr[5] = "    ";
                        for (int k = 0; k < vertical_block_len; ++k) {
                            sprintf(numStr, "%c%c%c%c", lines[0][offset + k], lines[1][offset + k], lines[2][offset + k], lines[3][offset + k]);
                            vertical_nums[k] = atoi(numStr);
                        }
                        break;
                    }
                }
                offset += chars_read;

                switch (op) {
                    case '+': {
                        long sum = 0;
                        for (int i = 0; i < 4; ++i) { sum += nums[i][column_number]; }
                        grand_total += sum;

                        sum = 0;
                        for (int i = 0; i < 4; ++i) { sum += vertical_nums[i]; }
                        grand_total_2 += sum;

                        column_number++;
                        break;
                    }
                    case '*': {
                        long product = 1;
                        for (int i = 0; i < 4; ++i) { product *= nums[i][column_number]; }
                        grand_total += product;

                        product = 1;
                        for (int i = 0; i < 4; ++i) { if (vertical_nums[i] != 0) product *= vertical_nums[i]; }
                        grand_total_2 += product;

                        column_number++;
                        break;
                    }
                }
            }
        } else {
            for (int count_read = sscanf(&input[offset], "%d%n", &num, &chars_read); count_read != EOF; count_read = sscanf(&input[offset], "%d%n", &num, &chars_read)) {
                nums[line_number][column_number++] = num;
                offset += chars_read;
            }
            line_number++;
        }
    }
    printf("Total: %ld\n", grand_total);
    printf("Total 2: %ld\n", grand_total_2);
}
