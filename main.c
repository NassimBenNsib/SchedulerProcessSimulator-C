#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libraries/structures.h"
#include "libraries/operations.h"
#include "libraries/enumerations.h"

void main(int argc, char * argv[]) {
  if (argc < 2) {
    change_text_color(Red_Text_Color);
    print_double_line();
    printf("Error! You must add configuration file\n");
    print_double_line();
    exit(-1);
  } else {
    emulator emulator;
    char command[200], string_quantum[4];

    init_emulator( & emulator);
    set_configuration_file_name( & emulator, argc, argv);
    importing_configuration_from_file( & emulator, False);

    if (strcmp(emulator.algorithm_name, DEFAULT_NAME) == 0) {
      choose_algorithm_name(emulator.algorithm_name);
    }
    strcpy(command, "./debugging/algorithms/");
    strcat(command, emulator.algorithm_name);
    strcat(command, " ");
    strcat(command, emulator.configuration_file_name);
    system(command);
  }
}