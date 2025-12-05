#include <stdbool.h>
#include <stdio.h>

typedef struct Range { long start; long end; bool merged; } Range;

int main () {
    FILE *fp = fopen("day5input.txt", "rb");
    Range range[512] = {0};
    long ids[2048] = {0};
    long a = 0; long b = 0;
    bool range_section = true;
    int range_count = 0, ids_count = 0;
    for (char input[256]; fgets(input, sizeof(input), fp);) {
        if (range_section) {
            int num_matched = sscanf(input, "%ld-%ld", &a, &b);
            if (num_matched > 0) {
                for (int i = 0; i < range_count; ++i) {
                    if (range[i].merged) continue;
                    if ((a >= range[i].start && a <= range[i].end) ||
                        (b >= range[i].start && b <= range[i].end) ||
                        (a <= range[i].start && b >= range[i].end)) {
                        range[i].merged = true;
                        a = a < range[i].start ? a : range[i].start;
                        b = b > range[i].end ? b : range[i].end;
                    }
                }
                range[range_count].start = a;
                range[range_count].end = b;
                range_count++;
            } else range_section = false;
        } else {
            long id;
            sscanf(input, "%ld", &id);
            ids[ids_count++] = id;
        }
    }

    unsigned long count_fresh = 0;
    for (int i = 0; i < ids_count; ++i) {
        for (int j = 0; j < range_count; ++j) {
            if (range[j].merged) continue;
            if (ids[i] >= range[j].start && ids[i] <= range[j].end) {
                count_fresh++;
                break;
            }
        }
    }
    printf("Count fresh IDs: %ld\n", count_fresh);
  
    count_fresh = 0;
    for (int i = 0; i < range_count; ++i) {
        if (range[i].merged) continue;
        count_fresh += (range[i].end - range[i].start + 1);
    }
    printf("Count fresh IDs 2: %ld\n", count_fresh);
}
