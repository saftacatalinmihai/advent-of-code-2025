#include <stdio.h>

int main() {
    FILE *fp = fopen("day1input.txt", "rb");
    char direction;
    int count = 0, times_dial_passes_0 = 0, times_dial_is_0 = 0, dial = 50;
    while (fscanf(fp, "%c%d\n", &direction, &count) != EOF) {
        switch (direction) {
            case 'L': {
                times_dial_passes_0 += (count / 100);
                count %= 100;
                if (count >= dial && dial !=0 ) { times_dial_passes_0++;}
                dial = (dial + 100 - count) % 100;
                break;
            }
            case 'R': {
                dial += count;
                times_dial_passes_0 += dial / 100;
                dial %= 100;
                break;
            }
        }
        if (dial == 0) times_dial_is_0++;
    }
    printf("Times dial is 0: %d\n", times_dial_is_0);
    printf("Times dial passes 0: %d\n", times_dial_passes_0);
    fclose(fp);
    return 0;
}
