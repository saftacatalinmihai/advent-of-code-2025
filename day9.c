
#include <stdbool.h>
#include <stdio.h>

#ifdef SMALL
#define TILES_HEIGHT "10"
#define TILES_WIDTH  "12"
#else
#define TILES_HEIGHT "98942"
#define TILES_WIDTH  "98947"
#endif 

#ifdef SMALL
#define MAX_RED_TILES 8
#else
#define MAX_RED_TILES 496
#endif
typedef struct Tile { int idx, row, col; } Tile;

long tile_count = 0;
Tile tiles[MAX_RED_TILES] = {0};

void print_tiles_to_file_svg(const char *filename, int rectangle[2][2], int highlighted_idx) {
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "<svg width=\"" TILES_WIDTH "\" height=\"" TILES_HEIGHT"\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    if (rectangle != NULL){ 
        fprintf(fp, "\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"none\" stroke=\"blue\" stroke-width=\"10\" >\n",
                rectangle[0][1], rectangle[0][0],
                rectangle[1][1] - rectangle[0][1],
                rectangle[1][0] - rectangle[0][0]
                );
        fprintf(fp, "\t\t<title>This is a blue circle</title>\n");
        fprintf(fp, "\t</rect>\n");
    }
    for (int i=0; i < tile_count; i++) {
        if (i == highlighted_idx) {
            fprintf(fp, "\t<rect x=\"%d\" y=\"%d\" width=\"1\" height=\"1\" fill=\"red\" />\n", tiles[i].col, tiles[i].row);
        } else {
            fprintf(fp, "\t<rect x=\"%d\" y=\"%d\" width=\"1\" height=\"1\" fill=\"black\" />\n", tiles[i].col, tiles[i].row);
        }
        fprintf(fp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />\n", tiles[i].col, tiles[i].row, tiles[(i+1)%tile_count].col, tiles[(i+1) % tile_count].row);

    }
    fprintf(fp, "</svg>\n");
    fclose(fp);
}

int main() {
    #ifdef SMALL
    FILE *fp = fopen("day9input_small.txt", "rb");
    #else 
    FILE *fp = fopen("day9input.txt", "rb");
    #endif

    int i,j;
    while (fscanf(fp, "%d,%d\n", &i, &j) != EOF) {
        tiles[tile_count] = (Tile){.idx = tile_count, .row = j, .col = i};
        tile_count++;
    }
    printf("Tile count: %ld\n", tile_count);

    print_tiles_to_file_svg("day9output.svg", NULL, -1);
    /* return 0; */

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
    // 4752484112
    //
    max_area = 0; 
    
    for (int tile_1=0; tile_1 < tile_count; tile_1++) {
        for (int tile_2=tile_1 + 1; ; tile_2 = (tile_2 + 1) % tile_count) {
            if (tile_1 == tile_2) break;
            Tile t1 = tiles[tile_1];
            Tile t2 = tiles[tile_2];

            /* printf("Considering tiles %d (%d, %d) and %d (%d, %d)\n", t1.idx, t1.col, t1.row, t2.idx, t2.col, t2.row); */
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


            /* long area = (long)(box[2][0] - box[0][0] + 1) * (long)(box[2][1] - box[0][1] + 1); */
            /* printf("Box corners: (%d,%d), (%d,%d), (%d,%d), (%d,%d), A: %ld\n", */
            /*     box[0][1], box[0][0], */
            /*     box[1][1], box[1][0], */
            /*     box[2][1], box[2][0], */
            /*     box[3][1], box[3][0], */
            /*     area */
            /* ); */

            bool found_tile_inside_rect = false;
            if (t1.row < t2.row && t1.col < t2.col) { // Upper Left to Lower Right
                /* printf("  Checking Upper Left to Lower Right\n"); */
                for (int i = t1.idx + 1; i != t2.idx; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row <= t2.row && t.col >= t1.col && (t.row > t1.row && t.col < t2.col)) {
                        found_tile_inside_rect = true;
                        /* printf("  Found tile inside rect at %d (%d,%d) between tiles %d (%d,%d) and %d (%d,%d)\n", */
                        /*     t.idx, t.col, t.row, */
                        /*     t1.idx, t1.col, t1.row, */
                        /*     t2.idx, t2.col, t2.row */
                        /* ); */
                        break;
                    }
                }
                for (int i = t2.idx + 1; i != t1.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row >= t1.row && t.col <= t2.col && (t.row < t2.row && t.col > t1.col)) {
                        found_tile_inside_rect = true;
                        /* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
                        /*     t.col, t.row, */
                        /*     t1.col, t1.row, */
                        /*     t2.col, t2.row */
                        /* ); */
                        break;
                    }
                }
            } else if (t1.row < t2.row && t1.col > t2.col) { // Upper Right to Lower Left
                for (int i = t1.idx + 1; i != t2.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row >= t1.row && t.col >= t2.col && (t.row < t2.row && t.col < t1.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
                for (int i = t2.idx + 1; i != t1.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row <= t2.row && t.col <= t1.col && (t.row > t1.row && t.col > t2.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
            } else if (t1.row > t2.row && t1.col > t2.col) { // Lower Right to Upper Left
                for (int i = t1.idx + 1; i != t2.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row >= t2.row && t.col <= t1.col && (t.row < t1.row && t.col > t2.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
                for (int i = t2.idx + 1; i != t1.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row <= t1.row && t.col >= t2.col && (t.row > t2.row && t.col < t1.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
            } else if (t1.row > t2.row && t1.col < t2.col) { // Lower Left to Upper Right
                for (int i = t1.idx + 1; i != t2.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row <= t1.row && t.col <= t2.col && (t.row > t2.row && t.col > t1.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
                for (int i = t2.idx + 1; i != t1.idx ; i = (i + 1) % tile_count) {
                    Tile t = tiles[i];
                    /* printf("    Checking tile %d (%d,%d)\n", t.idx, t.col, t.row); */
                    if (t.row >= t2.row && t.col >= t1.col && (t.row < t1.row && t.col < t2.col)) {
                        found_tile_inside_rect = true;
/* printf("  Found tile inside rect at (%d,%d) between tiles (%d,%d) and (%d,%d)\n", */
/*                             t.col, t.row, */
/*                             t1.col, t1.row, */
/*                             t2.col, t2.row */
/*                         ); */
                        break;
                    }
                }
            }

            if (!found_tile_inside_rect) {
                long area = (long)(box[2][0] - box[0][0] + 1) * (long)(box[2][1] - box[0][1] + 1 );
                if (area > max_area) { 
                    max_area = area; 
                    printf("  New max area % 12ld found for box corners: (%d,%d), (%d,%d), (%d,%d), (%d,%d), based on tiles (%d, %d), (%d, %d)\n",
                        max_area,
                        box[0][1], box[0][0],
                        box[1][1], box[1][0],
                        box[2][1], box[2][0],
                        box[3][1], box[3][0],
                        t1.col, t1.row,
                        t2.col, t2.row
                    );
                    print_tiles_to_file_svg("day9part2maxarea.svg", 
                                            (int [2][2]){
                                            {box[0][0], box[0][1]},
                                            {box[2][0], box[2][1]}},
                                            -1);
                    // 4534328125 - too high
                    // 4623607595
                    /* getchar(); */
                }
            }
        }
    }
}
