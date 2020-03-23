#include <stdio.h>

#include "life.h"

void print_error(char *error) {
    fprintf(stderr, "\e[1;31mErr: %s\e[0m\n\n", error);
}

void help() {
    printf("▟███▙ ▟███▙ █▙  ▟█ ████\n");
    printf("█     █   █ █▜▙▟▛█ █\n");
    printf("█ ███ █   █ █ ▝▘ █ ████\n");
    printf("█   █ █████ █    █ █\n");
    printf("▜███▛ █   █ █    █ ████\n");
    printf("\n");
    printf("▟███▙ ████   █    █ ████ ████\n");
    printf("█   █ █      █    █ █    █\n");
    printf("█   █ ████   █    █ ████ ████\n");
    printf("█   █ █      █    █ █    █\n");
    printf("▜███▛ █      ████ █ █    ████\n");
    printf("\n");
    printf("\n");
    printf("Usage:\n");
    printf("    life OPTIONS\n");
    printf("    life_ovk OPTIONS\n");
    printf("\n");
    printf("Options:\n");
    printf("    -n GEN_NUMBER\n");
    printf("        Number of Game of Life\n");
    printf("        generations to generate.\n");
    printf("\n");
    printf("        GEN_NUMBER = 0 will not create\n");
    printf("        new generations, just output\n");
    printf("        a PNG of the current generation.\n");
    printf("        GEN_NUMBER > 0 will create\n");
    printf("        new generations.\n");
    printf("        GEN_NUMBER < 0 is not allowed.\n");
    printf("        \n");
    printf("    -file INPUT_FILE\n");
    printf("        The initial state of the \n");
    printf("        system\n");
    printf("        \n");
    printf("    -out OUTPUT_DIRECTORY (optional) \n");
    printf("        Directory where the output\n");
    printf("        files will be saved to.\n");
    printf("\n");
    printf("    -wrap (optional)\n");
    printf("        The edges will wrap around,\n");
    printf("        \"removing\" boundaries from the\n");
    printf("        board.\n");
    printf("\n");
    printf("PNG Options:\n");
    printf("    -png-circles (optional) \n");
    printf("        Make cells in the output PNG\n");
    printf("        circular.\n");
    printf("\n");
    printf("    -png-size SIZE (optional) \n");
    printf("        Set the size of the cells in\n");
    printf("        the output PNG. Has to be\n");
    printf("        greater than 0.\n");
    printf("        Default = 1\n");
    printf("\n");
    printf("    -png-overkill OVK_FILE (optional)\n");
    printf("        The path to an Overkill shader.\n");
    printf("        This option is used only by the\n");
    printf("        version of Life compiled with\n");
    printf("        Overkill support.\n");
}