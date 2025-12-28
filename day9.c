
#include <stdbool.h>
#include <stdio.h>

#define MAX_RED_TILES 496
typedef struct Tile { int idx, row, col; } Tile;

long tile_count = 0;
Tile tiles[MAX_RED_TILES] = {0};

int main() {
    FILE *fp = fopen("day9input.txt", "rb");

    int i,j;
    while (fscanf(fp, "%d,%d\n", &i, &j) != EOF) {
        tiles[tile_count] = (Tile){.idx = tile_count, .row = j, .col = i};
        tile_count++;
    }

    long max_area = 0;
    for (int i=0; i < tile_count; i++) {
        for (int j=i+1; j < tile_count; j++) {
            int l1, l2;
            if (tiles[i].row < tiles[j].row) { l1 = tiles[j].row - tiles[i].row; }
            else { l1 = tiles[i].row - tiles[j].row; }

            if (tiles[i].col < tiles[j].col) { l2 = tiles[j].col - tiles[i].col; }
            else { l2 = tiles[i].col - tiles[j].col; }

            long area = (long)(l1 + 1) * (long)(l2 + 1);
            if (area > max_area) { max_area = area; }
        }
    }
    printf("Part 1: %ld\n", max_area);

    max_area = 0; 
    for (int tile_1=0; tile_1 < tile_count; tile_1++) {
        for (int tile_2=tile_1 + 1; tile_2 < tile_count; tile_2++) {
            if (tile_1 == tile_2) break;
            Tile t1 = tiles[tile_1];
            Tile t2 = tiles[tile_2];
            if (t1.row == t2.row || t1.col == t2.col) continue;

            int box[4][2] = {0}; // UpperLeft, UpperRight, LowerRight, LowerLeft
            if (t1.row > t2.row && t1.col > t2.col) { 
                box[0][0] = t2.row; box[0][1] = t2.col;
                box[1][0] = t2.row; box[1][1] = t1.col;
                box[2][0] = t1.row; box[2][1] = t1.col;
                box[3][0] = t1.row; box[3][1] = t2.col;
            } else if (t1.row > t2.row && t1.col < t2.col) {
                box[0][0] = t2.row; box[0][1] = t1.col;
                box[1][0] = t2.row; box[1][1] = t2.col;
                box[2][0] = t1.row; box[2][1] = t2.col;
                box[3][0] = t1.row; box[3][1] = t1.col;
            } else if (t1.row < t2.row && t1.col > t2.col) {
                box[0][0] = t1.row; box[0][1] = t2.col;
                box[1][0] = t1.row; box[1][1] = t1.col;
                box[2][0] = t2.row; box[2][1] = t1.col;
                box[3][0] = t2.row; box[3][1] = t2.col;
            } else {
                box[0][0] = t1.row; box[0][1] = t1.col;
                box[1][0] = t1.row; box[1][1] = t2.col;
                box[2][0] = t2.row; box[2][1] = t2.col;
                box[3][0] = t2.row; box[3][1] = t1.col;
            }

            bool found_tile_crossing_into_area = false;
            for (int i = t1.idx + 1; ; i = (i + 1) % tile_count) {
                if (i == t1.idx) break;

                Tile t = tiles[i];
                Tile tp = tiles[(i == 0) ? tile_count - 1 : i - 1];

                if (t.row == tp.row) {
                    if (box[0][0] < t.row && t.row < box[2][0]) {
                        if (tp.col >= box[1][1] && t.col < box[1][1]) {
                            found_tile_crossing_into_area = true;
                            break;
                        }
                        if (tp.col <= box[0][1] && t.col >= box[0][1]) {
                            found_tile_crossing_into_area = true;
                            break;
                        }
                    }
                } else {
                    if (box[0][1] < t.col && t.col < box[2][1]) {
                        if (tp.row >= box[2][0] && t.row < box[2][0]) {
                            found_tile_crossing_into_area = true;
                            break;
                        }
                        if (tp.row <= box[0][0] && t.row >= box[0][0]) {
                            found_tile_crossing_into_area = true;
                            break;
                        }
                    }
                }
            }

            if (!found_tile_crossing_into_area) {
                long area = (long)(box[2][0] - box[0][0] + 1) * (long)(box[2][1] - box[0][1] + 1 );
                if (area > max_area) { max_area = area; }
            }
        }
    }
    printf("Part 2: %ld\n", max_area);
}
