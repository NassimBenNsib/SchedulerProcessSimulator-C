#include <stdlib.h>
#include <stdio.h>
#include "../libraries/structures.h"
#include "../libraries/operations.h"
#include "../libraries/enumerations.h"


/************************************************** Start Algorithm **************************************************/

void start_algorithm(emulator * emulator) {
  int current_time = 0, last_executed_time = 0, iteration = 0;
  execution_history execution_history;
  process * current_process = NULL, * shortest_job_process = NULL;
  puts("Shortest Remaining Time (SRT) Scheduling");
  printf("================== Before Execution ======================\n");
  check_update( * emulator, True);
  printf("\n\n**************************** Simulation Of Execution ****************************");

  while (!is_list_process_empty(emulator -> list_incoming_process) || !is_list_process_empty(emulator -> list_waiting_process)) {
    shift_coming_process_to_list_waiting_process( & ( * emulator), last_executed_time, current_time);
    printf("\n\n================== Iteration %d ======================\n", iteration);
    printf("\n==>Current Time : %d\n", current_time);
    check_update( * emulator, True);
    if (is_list_process_empty(emulator -> list_waiting_process)) {
      current_process = get_first_incoming_process(emulator -> list_incoming_process);
      printf("\n==>There are no process : between %d-%d :\n", current_time, current_process -> arrival_time);
      current_time = current_process -> arrival_time;
    } else {
      shortest_job_process = get_shortest_job_process(emulator -> list_waiting_process);
      if (current_process == NULL || shortest_job_process != current_process) {
        if (current_process != NULL && shortest_job_process != current_process) {
          add_tail_execution_history_list( & emulator -> list_execution_history, execution_history);
        }
        init_execution_history( & execution_history);
      }
      current_process = shortest_job_process;
      printf("\n==>Executing Process : %s\n", current_process -> name);

      execute_process(current_process, 1, current_process -> priority, & current_time, & execution_history);
      if (execution_history.is_finished) {
        shift_process_from_list_to_other( & emulator -> list_waiting_process, & emulator -> list_finished_process, current_process);
        add_tail_execution_history_list( & emulator -> list_execution_history, execution_history);
        current_process = NULL;
      }
    }
    iteration++;
  }
  printf("\n================== Last Iteration %d ======================\n", iteration);
  printf("\n==> Current Time : %d\n", current_time);
  check_update( * emulator, True);

  printf("\n\n**************************** List Of Process Before Execution ****************************");
  show_table_process( & emulator -> list_process);
  printf("\n\n**************************** List Of Finished Process ****************************");
  show_table_finished_process( & emulator -> list_finished_process);
  printf("\n\n**************************** List Of Execution History ****************************");
  show_table_execution_history( & emulator -> list_execution_history);
}

/************************************************** Start Emulator **************************************************/

void start_emulator(int number_arguments, char * arguments[]) {
  emulator emulator;
  init_emulator( & emulator);
  set_configuration_file_name( & emulator, number_arguments, arguments);
  set_algorithm_name( & emulator, "Shortest Remaining Time (SRT) Scheduling");
  importing_configuration_from_file( & emulator, True);
  start_algorithm( & emulator);
}

/************************************************** Main Function **************************************************/

void main(int argc, char * argv[]) {
  start_emulator(argc, argv);
}