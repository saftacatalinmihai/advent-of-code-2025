#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int run_distances_count = 0;
double  distance(int a[3], int b[3]) {
    run_distances_count++;
    return sqrt(pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2) + pow(b[2] - a[2], 2));
}

typedef struct {
    double dist;
    bool checked;
} Cell;

int main() {
    FILE *fp = fopen("day8input.txt", "rb");
    int junctions[1000][3] = {0};
    int line_number = 0;
    for (char input[256]; fgets(input, sizeof(input), fp);) {
        int x, y, z;
        sscanf(input, "%d,%d,%d", &x, &y, &z);
        junctions[line_number][0] = x;
        junctions[line_number][1] = y;
        junctions[line_number][2] = z;
        /* printf("%000d: X: %d Y: %d Z: %d\n", line_number, junctions[line_number][0], junctions[line_number][1], junctions[line_number][2]); */
        line_number++;
    }

    Cell *distances = calloc(1000, 1000 * sizeof(Cell));
    for (int i = 0; i < line_number; ++i) {
        for (int j = 0; j < line_number; ++j) {
            if (i == j) continue;
            if (distances[i* 1000 + j].dist == 0) {
                double dist = distance(junctions[i], junctions[j]);
                distances[i * 1000 + j].dist = dist;
                distances[j * 1000 + i].dist = dist;
            }
        }
    }
    printf("Calculated distances\n");
    printf("Ran distance function %d times\n", run_distances_count);

    double smallest_distance = 0.0;
    while (smallest_distance >= 0.0) {
        smallest_distance = -1.0;
        int from = 0, to = 0;

        for (int i = 0; i < line_number; ++i) {
            double min_distance = -1.0;
            int closest_junction = -1;
            for (int j = 0; j < line_number; ++j) {
                if (i == j) continue;
                if (distances[i * 1000 + j].checked == false) {
                    double dist = distances[i * 1000 + j].dist;
                    if (min_distance < 0 || dist < min_distance) {
                        min_distance = dist;
                        closest_junction = j;
                        if (smallest_distance < 0 || dist < smallest_distance) {
                            smallest_distance = dist;
                            from = i;
                            to = j;
                            distances[i * 1000 + j].checked = true;
                            distances[j * 1000 + i].checked = true;
                        }
                    }
                }
            }
            /* printf("Junction %d closest to Junction %d with distance %.2f\n", i, closest_junction, min_distance); */
        }
        /* printf("Smallest distance between any two junctions: %.2f, %d->%d\n", smallest_distance, from, to); */
    }
    /* for (int i = 0; i < 1000; ++i) { */
    /*     for (int j = 0; j < 1000; ++j) { */
    /*         printf("%d ", distances[i * 1000 + j].checked); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    printf("Done\n");

    int count_circuits = 0;
}
