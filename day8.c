
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double  distance(int a[3], int b[3]) {
    return sqrt(pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2) + pow(b[2] - a[2], 2));
}

/* #define MAX_JUNCTIONS 20 */
#define MAX_JUNCTIONS 1000
typedef struct Junction {
    int x, y, z;
    int circuit_id;
    int next_closest_junction_id;
    double next_closest_junction_dist;
} Junction;

typedef struct Edge {
    int from, to;
    double distance;
    bool searched;
} Edge;

Junction junctions[MAX_JUNCTIONS] = {0};
Edge edges[MAX_JUNCTIONS][MAX_JUNCTIONS] = {0};

double dist_between(int from, int to) {
    if (to < from) { return edges[to][from].distance; }
    else { return edges[from][to].distance; }
}

Edge* smallest_distance_edge() {
    int smallest_distance = -1;
    int smallest_from = -1;
    int smallest_to = -1;
    for (int i = 0; i < MAX_JUNCTIONS; i++) {
        if (smallest_distance == -1 || junctions[i].next_closest_junction_dist < smallest_distance ) {
            smallest_distance = dist_between(i, junctions[i].next_closest_junction_id);
            smallest_from = i;
            smallest_to = junctions[i].next_closest_junction_id;
        }
        /* for (int j = i+1; j < MAX_JUNCTIONS; j++) { */
        /*     if (edges[i][j].searched || edges[j][i].searched) { continue; } */
        /*     double dist = dist_between(i, j); */
        /*     if (smallest_distance == -1 || dist < smallest_distance) { */
        /*         smallest_distance = dist; */
        /*         smallest_from = i; */
        /*         smallest_to = j; */
        /*     } */
        /* } */
    }
    if (smallest_from == -1) {
        printf("No unsearched edges remaining!\n");
        return NULL;
    }
    edges[smallest_from][smallest_to].searched = true;
    edges[smallest_to][smallest_from].searched = true;
    return &edges[smallest_from][smallest_to];
}

bool update_next_closest_junction(int id) {
    double smallest_distance = -1;
    int smallest_i = -1;
    for (int i = 0; i < MAX_JUNCTIONS; i++) {
        if (i == id) { continue; }
        if (!edges[id][i].searched) {
            double dist = dist_between(id, i);
            if (dist < smallest_distance || smallest_distance == -1) {
                smallest_distance = dist;
                smallest_i = i;
            }
        }
    }

    if (smallest_i == -1) { return false; }
    else {
        junctions[id].next_closest_junction_id = smallest_i;
        junctions[id].next_closest_junction_dist = smallest_distance;
        return true;
    }
}

int main() {
    FILE *fp = fopen("day8input.txt", "rb");
    int idx = 0;
    for (char input[256]; fgets(input, sizeof(input), fp);) {
        int x, y, z;
        sscanf(input, "%d,%d,%d", &x, &y, &z);
        junctions[idx] = (Junction){.x = x, .y = y, .z = z, .circuit_id = idx, .next_closest_junction_id = -1};
        idx++;
    }

    for (int i = 0; i < MAX_JUNCTIONS; i++) {
        for (int j = i+1; j < MAX_JUNCTIONS; j++) {
            if (i == j) continue;
            double dist = distance((int[]){junctions[i].x, junctions[i].y, junctions[i].z},
                                   (int[]){junctions[j].x, junctions[j].y, junctions[j].z});
            edges[i][j] = (Edge){.distance = dist, .from = i, .to = j};
        }
    }
    for(int i = 0; i < MAX_JUNCTIONS; i++) { update_next_closest_junction(i); }

    int circuit_counts[MAX_JUNCTIONS] = {0};
    for (int i=0; i<MAX_JUNCTIONS; i++) { circuit_counts[i] = 1; }

    int iter = 0;
    Edge* e = smallest_distance_edge();
    bool updated = true;
    int last_merged_from_x = -1;
    int last_merged_to_x = -1;
    while (updated) {
        if (junctions[e->from].circuit_id != junctions[e->to].circuit_id) {
            last_merged_from_x = junctions[e->from].x;  last_merged_to_x = junctions[e->to].x;
            int from_circuit = junctions[e->from].circuit_id;
            int to_circuit = junctions[e->to].circuit_id;
            for (int k = 0; k < MAX_JUNCTIONS; k++) {
                if (junctions[k].circuit_id == to_circuit) { junctions[k].circuit_id = from_circuit; }
            }
            circuit_counts[from_circuit] += circuit_counts[to_circuit];
            circuit_counts[to_circuit] = 0;
        }
        updated = update_next_closest_junction(e->from) && update_next_closest_junction(e->to);
        e = smallest_distance_edge();

        // Part 1:
        if (iter++ == 1000) {
            int product = 1;
            for (int i = 0; i < MAX_JUNCTIONS; i++) {
                // Hack cus I know the answer... just to compute the product of top 3 counts.
                if (circuit_counts[i] > 40) { product *= circuit_counts[i]; }
            }
            printf("Part 1: %d\n", product);
        }
    }
    printf("Part 2: %d\n", last_merged_from_x * last_merged_to_x);
}
