#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Machine {
    uint16_t indicator_light_diagram;
    uint16_t button_wiring_schematic[32];
    int button_groups_count;
    int joltage_requirements[32];
} Machine;

/* #define MAX_MACHIENS 3 */
#define MAX_MACHIENS 177
Machine machines[MAX_MACHIENS] = {0};

void print_button_wiring_schematic(uint16_t button_wiring) {
    for (int bit = 0; bit < 16; bit++) {
        if (button_wiring & (1U << bit)) {
            printf(" %d", bit);
        }
    }
}

void print_light_diagram(uint16_t light_diagram) {
    for (int bit = 0; bit < 16; bit++) {
        if (light_diagram & (1U << bit)) { printf("#"); } else { printf("."); }
    }
}

void Machines_print() {
    for (int i = 0; i < MAX_MACHIENS; i++) {
        printf("Machine %d:\n", i+1);
        printf(" Indicator Light Diagram: %d ", machines[i].indicator_light_diagram);
        print_light_diagram(machines[i].indicator_light_diagram);
        printf("\n");
        printf(" Button Wiring Schematic:\n");
        for (int j = 0; j < machines[i].button_groups_count; j++) {
            printf("  Group %d:", j+1);
            print_button_wiring_schematic(machines[i].button_wiring_schematic[j]);
            printf("\n");
        }
    }
}

int main() {
    /* FILE *fp = fopen("day10input_small.txt", "rb"); */
    FILE *fp = fopen("day10input.txt", "rb");
    char input[1024];
    int count = 0;
    while (fgets(input, sizeof(input), fp)) {
        int char_idx = 1;
        uint16_t indicator_light_diagram = 0;
        while (input[char_idx] != ']') {
            if (input[char_idx] == '#') { indicator_light_diagram |= (1U << (char_idx - 1)); }
            char_idx++;
        }
        machines[count].indicator_light_diagram = indicator_light_diagram;

        int button_group = 0;
        while (input[char_idx++] != '{') {
            while (input[char_idx] != ')') {
                if (input[char_idx] == ',' || input[char_idx] == '(' || input[char_idx] == ' ') { char_idx++; continue; }
                machines[count].button_wiring_schematic[button_group] |= (1U << (input[char_idx++] - '0'));
            }
            char_idx += 2;
            button_group++;
        }
        machines[count++].button_groups_count = button_group;
    }

    /* Machines_print(); */

    int min_iter = 0;
    for (int machine_idx = 0; machine_idx < MAX_MACHIENS; machine_idx++) {
        Machine machine = machines[machine_idx];
        uint16_t light_diagrams_to_check[512] = {0};
        int light_diagrams_count = 1;
        bool checked_diagrams[1024] = {false};
        bool found = false;
        int iteration = 0;
        while (!found) {
            iteration++;
            uint16_t new_light_diagrams_to_check[512] = {0};
            int new_light_diagrams_count = 0;
            for (int ld_idx = 0; ld_idx < light_diagrams_count; ld_idx++) {
                if (found) { break; }
                uint16_t start_light_diagram = light_diagrams_to_check[ld_idx];
                for (int button_group = 0; button_group < machine.button_groups_count; button_group++) {
                    uint16_t button_wiring = machine.button_wiring_schematic[button_group];
                    uint16_t new_light_diagram = start_light_diagram ^ button_wiring;
                    if (new_light_diagram == machine.indicator_light_diagram) {
                        found = true;
                        break;
                    } else {
                        if (checked_diagrams[new_light_diagram]) { continue; }
                        else {
                            checked_diagrams[new_light_diagram] = true;
                            new_light_diagrams_to_check[new_light_diagrams_count++] = new_light_diagram;
                        }
                    }
                }
            }
            light_diagrams_count = new_light_diagrams_count;
            for (int i = 0; i < new_light_diagrams_count; i++) {
                light_diagrams_to_check[i] = new_light_diagrams_to_check[i];
            }
        }
        min_iter += iteration;
    }
    printf("Part 1: %d\n", min_iter);
}
