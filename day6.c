#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("day6input.txt", "rb");

    int nums[6][4 * 1024] = {0}, line = 0, count_nums = 0;
    long grand_total = 0;
    for (char input[4 * 1024]; fgets(input, sizeof(input), fp);) { 
        int num = 0, offset = 0, chars_read = 0, i = 0;
        if (strchr(input, '+') != NULL) {
            char op;
            for (int count_read = sscanf(&input[offset], "%c%n", &op, &chars_read); count_read != EOF; count_read = sscanf(&input[offset], "%c%n", &op, &chars_read)) {
                switch (op) {
                    case '+': {
                        long sum = 0;
                        for (int j = 0; j < line; ++j) {
                            sum += nums[j][i];
                        }
                        grand_total += sum;
                        i++;
                        break;
                    }
                    case '*': {
                        long product = 1;
                        for (int j = 0; j < line; ++j) {
                            product *= nums[j][i];
                        }
                        grand_total += product;
                        i++;
                        break;
                    }
                }
                offset += chars_read;
            }
        } else {
            for (int count_read = sscanf(&input[offset], "%d%n", &num, &chars_read); count_read != EOF; count_read = sscanf(&input[offset], "%d%n", &num, &chars_read)) {
                nums[line][i++] = num;
                offset += chars_read;
                if (line == 0) count_nums++;
            }
            line++;
        }
    }
    printf("Total: %ld\n", grand_total);
    // 5361735137219
}
