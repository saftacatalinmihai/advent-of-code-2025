#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Range { long start; long end; bool merged; } Range;

int main () {
    FILE *fp = fopen("day5input.txt", "rb");
    Range ranges[512] = {0};
    long ids[2048] = {0};
    long a = 0; long b = 0;
    bool range_section = true;
    int ranges_count = 0, ids_count = 0;
    for (char input[256]; fgets(input, sizeof(input), fp);) {
        if (range_section) {
            int num_matched = sscanf(input, "%ld-%ld", &a, &b);
            if (num_matched > 0) {
                for (int i = 0; i < ranges_count; ++i) {
                    if (ranges[i].merged) continue;
                    if ((a >= ranges[i].start && a <= ranges[i].end) ||
                        (b >= ranges[i].start && b <= ranges[i].end) ||
                        (a <= ranges[i].start && b >= ranges[i].end)) {
                        ranges[i].merged = true;
                        a = a < ranges[i].start ? a : ranges[i].start;
                        b = b > ranges[i].end ? b : ranges[i].end;
                    }
                }
                ranges[ranges_count].start = a;
                ranges[ranges_count].end = b;
                ranges_count++;
            } else range_section = false;
        } else {
            long id;
            sscanf(input, "%ld", &id);
            ids[ids_count++] = id;
        }
    }

    unsigned long count_fresh = 0;
    for (int i = 0; i < ids_count; ++i) {
        for (int j = 0; j < ranges_count; ++j) {
            if (ranges[j].merged) continue;
            if (ids[i] >= ranges[j].start && ids[i] <= ranges[j].end) {
                count_fresh++;
                break;
            }
        }
    }
    printf("Count fresh IDs: %ld\n", count_fresh);
  
    count_fresh = 0;
    for (int i = 0; i < ranges_count; ++i) {
        if (ranges[i].merged) continue;
        count_fresh += (ranges[i].end - ranges[i].start + 1);
    }

    printf("Count fresh IDs 2: %ld\n", count_fresh);
}
