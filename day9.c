
#include <stdbool.h>
#include <stdio.h>

#define TEST
#ifdef TEST
#define TILES_HEIGHT "10"
#define TILES_WIDTH  "12"
#else
#define TILES_HEIGHT "98242"
#define TILES_WIDTH  "98147"
#endif 

#ifdef TEST
#define MAX_RED_TILES 8
#else
#define MAX_RED_TILES 496
#endif
typedef struct Tile { int i,j; } Tile;

long tile_count = 0;
Tile tiles[MAX_RED_TILES] = {0};

void print_tiles_to_file_svg(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "<svg width=\"" TILES_WIDTH "\" height=\"" TILES_HEIGHT"\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    for (int i=0; i < tile_count; i++) {
        fprintf(fp, "\t<rect x=\"%d\" y=\"%d\" width=\"100\" height=\"100\" fill=\"black\" />\n", tiles[i].j, tiles[i].i);
    }
    fprintf(fp, "</svg>\n");
    fclose(fp);
}

int main() {
    #ifdef TEST
    FILE *fp = fopen("day9input_small.txt", "rb");
    #else 
    FILE *fp = fopen("day9input.txt", "rb");
    #endif

    int i,j;
    while (fscanf(fp, "%d,%d\n", &i, &j) != EOF) {
        tiles[tile_count++] = (Tile){.i = j, .j = i};
    }

    /* print_tiles_to_file_svg("day9output.svg"); */

    long max_area = 0;
    for (int i=0; i<tile_count; i++) {
        for (int j=i+1; j<tile_count; j++) {
            int l1, l2;
            if (tiles[i].i < tiles[j].i) { l1 = tiles[j].i - tiles[i].i; }
            else { l1 = tiles[i].i - tiles[j].i; }

            if (tiles[i].j < tiles[j].j) { l2 = tiles[j].j - tiles[i].j; }
            else { l2 = tiles[i].j - tiles[j].j; }

            long area = (long)(l1 + 1) * (long)(l2 + 1);
            if (area > max_area) { max_area = area; }
        }
    }

    printf("Part 1: %ld\n", max_area);
    // 4752484112
}
