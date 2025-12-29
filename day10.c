#include <stdint.h>
#include <stdio.h>

typedef struct ButtonGroup {
    int buttons[31];
    int count;
} ButtonGroup;

typedef struct Machine {
    uint16_t indicator_light_diagram;
    ButtonGroup button_wiring_schematic[32];
    int button_groups_count;
    int joltage_requirements[32];
} Machine;

#define MAX_MACHIENS 3
Machine machines[MAX_MACHIENS] = {0};

void Machines_print() {
    for (int i = 0; i < MAX_MACHIENS; i++) {
        printf("Machine %d:\n", i+1);
        printf(" Indicator Light Diagram: 0x%04X\n", machines[i].indicator_light_diagram);
        printf(" Button Wiring Schematic:\n");
        for (int j = 0; j < machines[i].button_groups_count; j++) {
            printf("  Group %d: ", j+1);
            for (int k = 0; k < machines[i].button_wiring_schematic[j].count; k++) {
                printf("%d ", machines[i].button_wiring_schematic[j].buttons[k]);
            }
            printf("\n");
        }
    }
}

int main() {
    FILE *fp = fopen("day10input_small.txt", "rb");
    char input[512];
    int count = 0;
    while (fgets(input, sizeof(input), fp)) {
        int char_idx = 1;
        uint16_t indicator_light_diagram = 0;
        while (input[char_idx++] != ']') {
            if (input[char_idx] == '#') { indicator_light_diagram |= (1U << (char_idx - 1)); }
        }
        machines[count].indicator_light_diagram = indicator_light_diagram;

        int button_group = 0;
        while (input[char_idx++] != '{') {
            while (input[char_idx] != ')') {
                if (input[char_idx] == ',' || input[char_idx] == '(' || input[char_idx] == ' ') { char_idx++; continue; }
                machines[count]
                    .button_wiring_schematic[button_group]
                    .buttons[machines[count].button_wiring_schematic[button_group].count++]
                    = input[char_idx] - '0';
                char_idx++;
            }
            char_idx += 2;
            button_group++;
        }
        machines[count++].button_groups_count = button_group;
    }

    Machines_print();

    return 0;
}
