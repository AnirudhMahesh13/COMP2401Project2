README

Names: Anirudh Mahesh, Abhi Bashyal
Student Numbers: 101195630, 101311631

Description: The purpose of this code is to simulate a space shuttle flying and its resource consumption while covering distance. It also uses multithreading in order for the manager to manage multiple rockets concurrently for quick responses to the events.

Key Features include:

Resource and System Management:
Creates and manages resources and systems with dynamic memory allocation.
Uses resizable arrays to store resources and systems efficiently.
Prevents memory leaks through careful memory allocation and cleanup.

Event Queue:
Implements a linked list-based event queue.
Prioritizes events by importance and order of arrival.
Supports dynamic addition and removal of events.

Multithreading and Synchronization:
Creates separate threads for systems and the manager.
Synchronizes shared data using semaphores for thread safety.
Ensures smooth and error-free multithreaded execution.


Compiling and Running the Program
---------------------------------
1. Open a terminal and navigate to the folder containing these files:
   - main.c
   - system.c
   - resouce.c
   - event.c
   - manager.c
   - defs.h
   - Makefile
   

2. Compile the program by typing:
   make

3. Run the program by typing:
    make run

4. clear the program by typing:
   make clean