#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_invalid_number_2(char* str_num) {
    int num_len = strlen(str_num);
    bool is_invalid = false;
    for (int stride_len = 1; stride_len <= num_len / 2; ++stride_len) {
        if (num_len % stride_len == 0) {
            bool all_match = true;
            for (int i = 0; i < num_len / stride_len - 1; i++) {
                if (memcmp(&str_num[i * stride_len],
                           &str_num[(i + 1) * stride_len], stride_len) != 0) {
                    all_match = false;
                    break;
                }
            }
            if (all_match) {
                is_invalid = true;
                break;
            }
        }
    }
    return is_invalid;
}

int main() {
    FILE *fp = fopen("day2input.txt", "rb");
    char input[1024];
    char comma[2] = ",", dash[2] = "-";

    while (fgets(input, sizeof(input), fp)) {
        char* interval;
        char* rest = input;
        interval = strtok_r(input, comma, &rest);

        long long invaid_sum = 0;
        long long invaid_sum_2 = 0;
        while (interval != NULL) {
            char* start;
            char* end;
            long start_int, end_int;

            start_int = atoll(strtok(interval, dash));
            end_int = atoll(strtok(NULL, dash));

            for(long i = start_int; i <= end_int; i++) {
                char str_num[16] = {0};
                sprintf(str_num, "%ld", i);

                // Part 1
                int l = strlen(str_num);
                if (l % 2 == 0 && memcmp(str_num, &(str_num[l/2]), l/2) == 0) {
                    invaid_sum += i;
                }

                // Part 2
                if (is_invalid_number_2(str_num)) {
                    invaid_sum_2 += i;
                }
            }

            interval = strtok_r(NULL, comma, &rest);
        }

        printf("Invalid sum: %lld\n", invaid_sum);
        printf("Invalid sum 2: %lld\n", invaid_sum_2);
    }
    return 0;
}
