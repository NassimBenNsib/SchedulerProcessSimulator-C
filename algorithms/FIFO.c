#include <stdlib.h>
#include <stdio.h>
#include "../libraries/structures.h"
#include "../libraries/operations.h"
#include "../libraries/enumerations.h"

/************************************************** Start Algorithm **************************************************/

void start_algorithm(emulator * emulator) {
  int current_time = 0, last_executed_time = 0, iteration = 0;
  process * current_process = NULL;
  puts("\nFirst-In, First-Out (FIFO/FCFS) Scheduling\n");
  printf("================== Before Execution ======================\n");
  check_update( * emulator, False);
  printf("\n\n**************************** Simulation Of Execution ****************************");
  while (!is_list_process_empty(emulator -> list_incoming_process) || !is_list_process_empty(emulator -> list_waiting_process)) {
    shift_coming_process_to_list_waiting_process( & ( * emulator), last_executed_time, current_time);
    printf("\n\n================== Iteration %d ======================\n", iteration);
    printf("\n==>Current Time : %d\n", current_time);
    check_update( * emulator, False);
    if (is_list_process_empty(emulator -> list_waiting_process)) {
      current_process = get_first_incoming_process(emulator -> list_incoming_process);
      printf("\n==>There are no process : between %d-%d :\n", current_time, current_process -> arrival_time);
      current_time = current_process -> arrival_time;
      current_process = get_first_incoming_process(emulator -> list_incoming_process);
      current_time = current_process -> arrival_time;
    } else {
      current_process = emulator -> list_waiting_process.head;
      execute_process( & ( * current_process), current_process -> execution_time, current_process -> priority, & current_time, NULL);
      shift_process_from_list_to_other( & emulator -> list_waiting_process, & emulator -> list_finished_process, current_process);
      printf("\n==>Executing Process : %s\n", current_process -> name);
      iteration++;
    }
  }
  printf("\n================== Last Iteration %d ======================\n", iteration);
  printf("\n==> Current Time : %d\n", current_time);
  check_update( * emulator, False);

  printf("\n\n**************************** List Of Process Before Execution ****************************");
  show_table_process( & emulator -> list_process);
  printf("\n\n**************************** List Of Finished Process ****************************");
  show_table_finished_process( & emulator -> list_finished_process);
}

/************************************************** Start Emulator **************************************************/

void start_emulator(int number_arguments, char * arguments[]) {
  emulator emulator;
  init_emulator( & emulator);
  set_configuration_file_name( & emulator, number_arguments, arguments);
  set_algorithm_name( & emulator, "First-In, First-Out (FIFO/FCFS) Scheduling ");
  importing_configuration_from_file( & emulator, True);
  start_algorithm( & emulator);
}

/************************************************** Main Function **************************************************/

void main(int argc, char * argv[]) {
  start_emulator(argc, argv);
}