#ifndef EMULATOR_OPERATIONS_H_INCLUDED
#define EMULATOR_OPERATIONS_H_INCLUDED

/************************************************** Importing Of Dependencies **************************************************/

#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "enumerations.h"

/************************************************** Console Operations **************************************************/

//Change Text Color Of Console
void change_text_color(enum text_color color) {
  printf("\033[1;%dm", color);
}

//Print Double Line
void print_double_line() {
  printf("\n======================================================================================================\n");
}

/************************************************** Process Operations **************************************************/

//Init Process
void init_process(process * process) {
  strcpy(process -> name, DEFAULT_NAME);
  process -> priority = DEFAULT_UNITY_VALUE;
  process -> current_priority = DEFAULT_UNITY_VALUE;
  process -> arrival_time = DEFAULT_UNITY_VALUE;
  process -> execution_time = DEFAULT_UNITY_VALUE;
  process -> remaining_execution_time = DEFAULT_UNITY_VALUE;
  process -> start_execution_time = DEFAULT_UNITY_VALUE;
  process -> end_execution_time = DEFAULT_UNITY_VALUE;
  process -> next = NULL;
  process -> previous = NULL;
}

//Execution Of Process
void execute_process(process * process, int execution_time, int new_priority, int * current_time, execution_history * execution_history) {
  if (execution_history != NULL) {
      if(!execution_history->process){
        execution_history -> start_execution_time = * current_time;
        execution_history -> process = process;
        execution_history -> next = NULL;
        execution_history -> previous = NULL;
      }
    execution_history -> priority = process -> priority;
    execution_history->is_finished = ((process->remaining_execution_time - execution_time ) == 0 ) ? True : False;
    execution_history -> executed_time += execution_time;
  }
  if (process -> execution_time == process -> remaining_execution_time) {
    process -> start_execution_time = * current_time;
  }
  process -> remaining_execution_time = process -> remaining_execution_time - execution_time;
  process -> current_priority = new_priority;
  if (!process -> remaining_execution_time) {
    process -> end_execution_time = * current_time + execution_time;
  }
    *current_time += execution_time;
}

/************************************************** List Of Process Operations **************************************************/

//Init List Of Process
void init_list_process(list_process * list_process) {
  list_process -> head = NULL;
  list_process -> tail = NULL;
}

//Add A Process To End Of The List
void add_tail_process_list(list_process * list_process, process data_process) {
  process * new_process = (struct process * ) malloc(sizeof(struct process));
  strcpy(new_process -> name, data_process.name);
  new_process -> arrival_time = data_process.arrival_time;
  new_process -> execution_time = data_process.execution_time;
  new_process -> priority = data_process.priority;
  new_process -> remaining_execution_time = new_process -> execution_time;
  new_process -> current_priority = new_process -> priority;
  new_process -> next = NULL;
  new_process -> previous = NULL;
  if (list_process -> tail == NULL) {
    list_process -> head = new_process;
    list_process -> tail = new_process;
  } else {
    list_process -> tail -> next = new_process;
    new_process -> previous = list_process -> tail;
    list_process -> tail = new_process;
  }
}

//Add A Process Address To End Of The List
void add_tail_address_process_list(list_process * list_process, process * new_process) {
  new_process -> next = NULL;
  new_process -> previous = NULL;
  if (list_process -> tail == NULL) {
    list_process -> head = new_process;
    list_process -> tail = new_process;
  } else {
    list_process -> tail -> next = new_process;
    new_process -> previous = list_process -> tail;
    list_process -> tail = new_process;
  }
}

//Test If List Is Empty
enum boolean is_list_process_empty(list_process list_process) {
  return list_process.tail == NULL ? True : False;
}

//Delete Process From List Of Process
void delete_process_list_process(list_process * list_process, process * process, enum boolean with_free_memory) {
  if (!is_list_process_empty( * list_process)) {
    if (list_process -> head == process) {
      if (list_process -> head == list_process -> tail) {
        list_process -> head = NULL;
        list_process -> tail = NULL;
      } else {
        list_process -> head = list_process -> head -> next;
        list_process -> head -> previous = NULL;
        process -> next = NULL;

      }
    } else if (list_process -> tail == process) {
      list_process -> tail = list_process -> tail -> previous;
      list_process -> tail -> next = NULL;
      process -> previous = NULL;
    } else {
      process -> next -> previous = process -> previous;
      process -> previous -> next = process -> next;
      process -> next = NULL,
        process -> previous = NULL;
    }

    if (with_free_memory == True) {
      free(process);
    }
  }
}

//shift Process From Frst List To Second List 
void shift_process_from_list_to_other(list_process * first_list, list_process * second_list, process * process) {
  delete_process_list_process( & ( * first_list), process, False);
  add_tail_address_process_list( & ( * second_list), process);
}

//Get First Incoming Process
process *get_first_incoming_process(list_process list_process){
    process *current_process = list_process.head, *target = current_process;
    while(current_process){
        if(current_process->arrival_time<target->arrival_time){
            target=current_process;
        }
        current_process = current_process->next;
    }
    return target;
}

//Get The Shortest Job Process
process *get_shortest_job_process(list_process list_process){
    process *current_process = list_process.head, *target = current_process;
    while(current_process){
        if(current_process->execution_time<target->execution_time){
            target=current_process;
        }
        current_process = current_process->next;
    }
    return target;
}

//Get The Last Came Process
process *get_last_came_process(list_process list_process){
    process *current_process = list_process.head, *target = current_process;
    while(current_process){
        if(current_process->arrival_time>target->arrival_time){
            target=current_process;
        }
        current_process = current_process->next;
    }
    return target;
}

process *get_highest_priority_process(list_process list_process){
    process *current_process = list_process.head, *target = current_process;
    while(current_process){
        if(current_process->priority>target->priority){
            target=current_process;
        }
        current_process = current_process->next;
    }
    return target;
}

//Get Number Of Process
int get_process_number(list_process * list_process) {
  process * current_process = list_process -> head;
  int number_process = 0;
  while (current_process) {
    current_process = current_process -> next;
    number_process++;
  }
  return number_process;
}

//Show All Process Names
void show_process_names(list_process * list_process) {
  process * current_process = list_process -> head;
  while (current_process) {
    puts(current_process -> name);
    current_process = current_process -> next;
  }
}

//Show All Process Details
void show_all_process_details(list_process * list_process) {
  process * current_process = list_process -> head;
  while (current_process) {
    printf("\n| %s | %d | %d | %d |\n", current_process -> name, current_process -> arrival_time, current_process -> execution_time, current_process -> priority);
    current_process = current_process -> next;
  }
}

//Show All Process Details
void show_table_finished_process(list_process * list_process) {
  process * current_process = list_process -> head;
  printf("\n\n\n");
    printf(" ===============================================================================================");
    printf("\n||               ||              ||                ||          ||            ||                ||");
    printf("\n||  Process Name || Arrival Time || Execution Time || Priority || Start Time || Finished Time  ||");
    printf("\n||               ||              ||                ||          ||            ||                ||");
    printf("\n ===============================================================================================\n");

  while (current_process) {
    printf("|| %-13s || %-12d || %-14d || %-8d || %-10d || %-14d ||", current_process -> name, current_process -> arrival_time, current_process -> execution_time, current_process -> priority,current_process->start_execution_time,current_process->end_execution_time);
    printf("\n ===============================================================================================\n");
    current_process = current_process -> next;
  }
}

//Show All Process Details
void show_table_process(list_process * list_process) {
  process * current_process = list_process -> head;
  printf("\n\n\n");
    printf(" ===============================================================");
    printf("\n||               ||              ||                ||          ||");
    printf("\n||  Process Name || Arrival Time || Execution Time || Priority ||");
    printf("\n||               ||              ||                ||          ||");
    printf("\n ===============================================================\n");

  while (current_process) {
    printf("|| %-13s || %-12d || %-14d || %-8d ||", current_process -> name, current_process -> arrival_time, current_process -> execution_time, current_process -> priority);
    printf("\n ===============================================================\n");
    current_process = current_process -> next;
  }
}
/************************************************** List Of Execution History Operations **************************************************/

//Init List Of Process
void init_list_execution_history(list_execution_history * list_execution_history) {
  list_execution_history->head = NULL;
  list_execution_history->tail = NULL;
}

//Add A Process To End Of The List
void add_tail_execution_history_list(list_execution_history * list_execution_history, execution_history data_execution_history) {
  execution_history * new_history = NULL;
  new_history = (execution_history*)malloc(sizeof(execution_history));
  new_history -> priority = data_execution_history.priority;
  new_history -> is_finished = data_execution_history.is_finished;
  new_history -> start_execution_time = data_execution_history.start_execution_time;
  new_history -> executed_time = data_execution_history . executed_time;
  new_history -> process = data_execution_history . process;
  new_history -> next = NULL;
  new_history -> previous = NULL;
  if (list_execution_history -> tail == NULL) {
    list_execution_history -> head = new_history;
    list_execution_history -> tail = new_history;
   }else {
    list_execution_history -> tail -> next = new_history;
    new_history -> previous = list_execution_history -> tail;
    list_execution_history -> tail = new_history;
  }
}

//Get Number Of History
int get_execution_history_number(list_execution_history * list_execution_history) {
  execution_history * current_history = list_execution_history -> head;
  int number_history = 0;
  while (current_history) {
    current_history = current_history -> next;
    number_history++;
  }
  return number_history;
}

//Show All Process Details
void show_all_execution_history_details(list_execution_history * list_execution_history) {
  execution_history * current_history = list_execution_history -> head;
  while (current_history) {
    printf("\n| %s | %d | %d | %d | %d |\n", current_history->process->name, current_history -> priority, current_history -> is_finished, current_history -> start_execution_time,current_history -> executed_time);
    current_history = current_history -> next;
  }
}

//Show All Execution History Details
void show_table_execution_history(list_execution_history * list_execution_history) {
  execution_history * current_history = list_execution_history -> head;
  printf("\n\n\n");
    printf(" ==============================================================================================");
    printf("\n||               ||               ||             ||               ||          ||              ||");
    printf("\n||  Process Name || Strating Time || Ending Time || Executed Time || Priority || Is finished ||");
    printf("\n||               ||               ||             ||               ||          ||              ||");
    printf("\n ==============================================================================================\n");

  while (current_history) {
    printf("|| %-13s || %-13d || %-11d || %-13d || %-8d || %-12s ||", current_history->process -> name, current_history -> start_execution_time,current_history->start_execution_time + current_history->executed_time ,current_history -> executed_time, current_history -> priority,(current_history->is_finished)?"Yes" : "No");
    printf("\n ==============================================================================================\n");
    current_history = current_history -> next;
  }
}


/************************************************** Execution History Operations **************************************************/

//Init Execution History
void init_execution_history(execution_history * execution_history) {
  execution_history -> priority = 0;
  execution_history -> is_finished = False;
  execution_history -> start_execution_time = 0;
  execution_history -> executed_time = 0;
  execution_history -> process = NULL;
  execution_history -> next = NULL;
  execution_history -> previous = NULL;
}

/************************************************** Input/Output && Data Operations **************************************************/

//Check The Content Type Of Readed Line
enum line_type get_line_type(char line[], process * process, emulator * emulator, enum boolean only_process_configuration) {
  if (strlen(line) == 1) {
    return Empty;
  } else if (strlen(line) > 2) {
    if (line[0] == '#' || (line[0] == '/' && line[0] == line[1])) {
      return Comment;
    }
    if (line[0] == '|') {
      sscanf(line, "| %s | %d | %d | %d |", process -> name, & process -> arrival_time, & process -> execution_time, & process -> priority);
      if (process -> priority == DEFAULT_UNITY_VALUE || process -> priority < 0 || process -> arrival_time < 0 || process -> execution_time < 0) {
        return Error;
      }
      return Process_Configuration;
    } else if (strstr(line, "Algorithm_Name")) {
      char algorithm_name[50];
      strcpy(algorithm_name, DEFAULT_NAME);
      sscanf(line, "Algorithm_Name=%s", algorithm_name);
      if (strcmp(algorithm_name, DEFAULT_NAME) == False) {
        return Error;
      }
      if (only_process_configuration == False) {
        strcpy(emulator -> algorithm_name, algorithm_name);
      }
      return Scheduler_Configuration;
    } else if (strstr(line, "Quantum")) {
      int quantum = -1;
      sscanf(line, "Quantum=%d", & quantum);
      if (quantum <= 0) {
        return Error;
      }
      if (only_process_configuration == False) {
        emulator -> quantum = quantum;
      }
      return Scheduler_Configuration;
    } else {
      return Error;
    }
  } else {
    return Error;
  }
}

/************************************************** Algorithms Files Operations **************************************************/

//Choose Algorithm
void choose_algorithm_name(char algorithm_name[]) {
  DIR * directory;
  struct dirent * dir;
  int algorithm_number = 0,test = 0;
  FILE *file = NULL;
  char path[200];
  directory = opendir("./algorithms");
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {
      if (strcmp(dir -> d_name, ".") && strcmp(dir -> d_name, "..") ) {
        dir -> d_name[strlen(dir -> d_name) - 2] = '\0';
        if (algorithm_number) {
          printf("%d- %s\n", algorithm_number, dir -> d_name);
        }
      }
      algorithm_number++;
    }
    do{
    printf("Choose your algorithm name : \n");
    scanf("%s",algorithm_name);
    strcpy(path,"./algorithms/");
    strcat(path,algorithm_name);
    strcat(path,".c");
    if( access( path, F_OK ) == 0 ){
      test=1;
    }
    }while(strlen(algorithm_name)<1 || test == 0);
    closedir(directory);
  }
}

//Get Number Of Algorithm
int get_algorithm_number() {
DIR * directory;
  struct dirent * dir;
  int number_algorithm = 0;
  directory = opendir("./algorithms");
  if (directory) {
    while ((dir = readdir(directory)) != NULL) {
      if (strcmp(dir -> d_name, ".") && strcmp(dir -> d_name, "..")) {
      number_algorithm++;
      }
    }
    closedir(directory);
  }
  return number_algorithm;
}

/************************************************** Emulator Operations **************************************************/

//Init Emulator
void init_emulator(emulator * emulator) {
  strcpy(emulator -> algorithm_name, DEFAULT_NAME);
  strcpy(emulator -> configuration_file_name, DEFAULT_CONFIGURATION_FILE_NAME);
  emulator -> quantum = 2;
  init_list_process( & emulator -> list_incoming_process);
  init_list_process( & emulator -> list_waiting_process);
  init_list_process( & emulator -> list_finished_process);
  init_list_process( & emulator -> list_process);
  init_list_execution_history( & emulator -> list_execution_history); 
}

//Importing Configurations & Data Of Emulator From File
void importing_configuration_from_file(emulator * emulator, enum boolean only_process_configuration) {
  FILE * file = fopen(emulator -> configuration_file_name, "r");
  enum line_type line_type;
  char buffer[MAX_BUFFER_SIZE];
  process data_process;
  int line_number = 0;

  if (file == NULL) {
    change_text_color(Red_Text_Color);
    print_double_line();
    printf("Error! Could not open file %s\n", emulator -> configuration_file_name);
    print_double_line();
    exit(-1);
  } else {
    while (feof(file) == False) {
      line_number++;
      fgets(buffer, MAX_BUFFER_SIZE, file);
      init_process( & data_process);

      switch (get_line_type(buffer, & data_process, emulator, only_process_configuration)) {
      case Process_Configuration:
        add_tail_process_list( & emulator -> list_incoming_process, data_process);
        add_tail_process_list( & emulator -> list_process, data_process);
        break;

      case Error:
        change_text_color(Red_Text_Color);
        buffer[strlen(buffer) - 1] = '\0';
        print_double_line();
        printf("\nError of structure of file in line %d : \"%s\"\n", line_number, buffer);
        print_double_line();
        exit(-1);
        break;
      }
    }
  }
  fclose(file);
}

//shift From coming Process To List Waiting Process
void shift_coming_process_to_list_waiting_process(emulator * emulator, int start_time, int end_time) {
  process * current_process, * target;
  int current_time = start_time;
  while (current_time <= end_time) {
    current_process = emulator -> list_incoming_process.head;
    while (current_process != NULL) {
      target = current_process;
      current_process = current_process -> next;
      if (target -> arrival_time == current_time) {
        shift_process_from_list_to_other( & emulator -> list_incoming_process, & emulator -> list_waiting_process, target);
      }
    }
    current_time++;
  }
}

//Set Configuration File Name
void set_configuration_file_name(emulator * emulator, int number_arguments, char * arguments[]) {
  if (number_arguments > 1) {
    strcpy(emulator -> configuration_file_name, arguments[1]);
  } else {
    change_text_color(Red_Text_Color);
    print_double_line();
    printf("\nThere are no configuration file !!\n");
    print_double_line();
    exit(-1);
  }
}

//Set Algorithm Name
void set_algorithm_name(emulator * emulator, char algorithm_name[]) {
  strcpy(emulator -> algorithm_name, algorithm_name);
}

//Show All Lists Update
void check_update(emulator emulator,int with_history) {
  printf("\n\n*** Incoming Process ***\n");
  show_all_process_details( & emulator.list_incoming_process);
  printf("\n\n*** Waiting ***\n");
  show_all_process_details( & emulator.list_waiting_process);
  printf("\n\n*** Funished ***\n");
  show_all_process_details( & emulator.list_finished_process);
  if(with_history){
  printf("\n\n*** History ***\n");
  show_all_execution_history_details( & emulator.list_execution_history);

  }
}

#endif // EMULATOR_OPERATIONS_H_INCLUDED
