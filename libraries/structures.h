#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

//Structure Of Process
typedef struct process {
  char name[10];
  int priority;
  int current_priority;
  int arrival_time;
  int execution_time;
  int remaining_execution_time;
  int start_execution_time;
  int end_execution_time;
  struct process * next;
  struct process * previous;
}
process;

//Structure Of List Process
typedef struct list_process {
  int number_process;
  struct process * head;
  struct process * tail;
}
list_process;

//Structure Of Process Execution History
typedef struct execution_history {
  int priority;
  int is_finished;
  int executed_time;
  int start_execution_time;
  struct process * process;
  struct execution_history *next;
  struct execution_history *previous;
}execution_history;

//Structure Of List Execution History
typedef struct list_execution_history{
  struct execution_history *head;
  struct execution_history *tail;
}list_execution_history;

//Structure Of Emulator
typedef struct emulator {
  char configuration_file_name[100];
  char algorithm_name[50];
  int quantum;
  struct list_process list_process;
  struct list_process list_incoming_process;
  struct list_process list_waiting_process;
  struct list_process list_finished_process;
  struct list_execution_history list_execution_history;
}
emulator;

#endif // STRUCTURES_H_INCLUDED