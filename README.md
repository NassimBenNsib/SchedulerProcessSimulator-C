# Scheduling Process Simulator

The Scheduling Process Simulator is a command-line tool developed in C that simulates various process scheduling algorithms. It allows you to define a set of processes with different attributes and then run different scheduling algorithms to observe how these processes are scheduled and executed.

## Table of Contents

- [Scheduling Process Simulator](#scheduling-process-simulator)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Supported Algorithms](#supported-algorithms)
  - [Directory Structure](#directory-structure)
  - [Installation Guide](#installation-guide)
  - [Steps](#steps)
  - [Run Simulator](#run-simulator)

## Introduction

This simulator is designed to help you understand and compare different process scheduling algorithms by simulating their execution on a set of predefined processes. It provides a flexible structure that allows you to easily add and modify algorithms and customize the simulation.

## Supported Algorithms
The following scheduling algorithms are currently supported:

-   First-In, First-Out (FIFO/FCFS) Scheduling
-   Last-In, First-Out (LIFO) Scheduling
-   Shortest Job First (SJF) Scheduling
-   Shortest Remaining Time (SRT) Scheduling
-   Static Priority Non-Preemptive Scheduling
-   Static Priority Preemptive Scheduling

## Directory Structure
-   algorithms/: Contains the source code for different scheduling algorithms.
-   debugging/: Contains compiled executable files and algorithm scripts.
-   libraries/: Contains header files and utility functions for the simulator.
-   main.c: The main program that handles configuration, algorithm selection, and - execution.
-   Makefile: Automates the compilation and execution process.

## Installation Guide

To get started, follow these steps:

1. Install the make Package: Start by installing the make package using the following command: `sudo apt-get install make`
2. Clone the repository to your local machine.
3. Ensure you have a C compiler installed (e.g., GCC).
4. Navigate to the project directory in your terminal.
5. Compile the Program: Run the provided Makefile to dynamically compile all the necessary files. The Makefile will prompt for permission to modify the files to ensure proper compilation `make`.


## Steps
-   The simulator takes a configuration file as input, which defines the list of processes with their attributes such as name, arrival time, execution time, and priority.

-   If no algorithm name is provided, the simulator will prompt you to choose an algorithm.

-   The simulator will then execute the chosen algorithm on the defined processes and display the execution simulation.

## Run Simulator
Follow these instructions to use the Scheduling Process Simulator:
1.  Run the Program: Execute the start file and provide the configuration file as an argument. For example:
```bash
./debugging/start ./configurations/default_configuration_file.config
```
2. Simulation: The program will read the configuration file and simulate the selected algorithm's logic. The simulation will show lists at each iteration, including:

-   Processes that have not yet arrived.
-   Processes waiting in the queue.
-   Processes that have finished execution.
-   Processes as ordered in the configuration file.
-   Process execution histories.
