#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

/* Event functions */

/**
 * Initializes an `Event` structure.
 *
 * Sets up an `Event` with the provided system, resource, status, priority, and amount.
 *
 * @param[out] event     Pointer to the `Event` to initialize.
 * @param[in]  system    Pointer to the `System` that generated the event.
 * @param[in]  resource  Pointer to the `Resource` associated with the event.
 * @param[in]  status    Status code representing the event type.
 * @param[in]  priority  Priority level of the event.
 * @param[in]  amount    Amount related to the event (e.g., resource amount).
 */
void event_init(Event *event, System *system, Resource *resource, int status, int priority, int amount) {
    event->system = system;
    event->resource = resource;
    event->status = status;
    event->priority = priority;
    event->amount = amount;
}

/* EventQueue functions */

/**
 * Initializes the `EventQueue`.
 *
 * Sets up the queue for use, initializing any necessary data (e.g., semaphores when threading).
 *
 * @param[out] queue  Pointer to the `EventQueue` to initialize.
 */
void event_queue_init(EventQueue *queue) {
    queue->head = NULL;
    queue->size = 0;
    sem_init(&queue->mutex,0,1);
}

/**
 * Cleans up the `EventQueue`.
 *
 * Frees any memory and resources associated with the `EventQueue`.
 * 
 * @param[in,out] queue  Pointer to the `EventQueue` to clean.
 */
void event_queue_clean(EventQueue *queue) {
    sem_destroy(&queue->mutex);
    EventNode *curr = queue->head;
    EventNode *next = NULL;

    while (curr!= NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }

    //queue->size = 0;
    //free(queue);
}

/**
 * Pushes an `Event` onto the `EventQueue`.
 *
 * Adds the event to the queue in a thread-safe manner, maintaining priority order (highest first).
 *
 * @param[in,out] queue  Pointer to the `EventQueue`.
 * @param[in]     event  Pointer to the `Event` to push onto the queue.
 */
void event_queue_push(EventQueue *queue, const Event *event) {
    // Allocate memory for new node and set it with event data
    EventNode *node = malloc(sizeof(EventNode));
    node->event = *event;

    // Wait for access to the queue 
    sem_wait(&queue->mutex);

    // Used to traverse through the queue to find correct spot for new node
    EventNode *curr = queue->head;
    EventNode *prev = NULL;

   // Traverse through the queue to find the correct spot based on priority
    while(curr!= NULL && curr->event.priority >= node->event.priority){
        prev = curr;
        curr = curr->next;
    }

    // Insert new node at the correct spot in the queue
    node->next = curr;
    if(prev == NULL){
        queue->head = node; // Insert at the head if no prev node exist
    }
    else{
    prev->next = node; // Link the prev node to the new node
    }

    // Increase size
    queue->size++;
    sem_post(&queue->mutex);

}

/**
 * Pops an `Event` from the `EventQueue`.
 *
 * Removes the highest priority event from the queue in a thread-safe manner.
 *
 * @param[in,out] queue  Pointer to the `EventQueue`.
 * @param[out]    event  Pointer to the `Event` structure to store the popped event.
 * @return               Non-zero if an event was successfully popped; zero otherwise.
 */
int event_queue_pop(EventQueue *queue, Event *event) {
   // Wait for access to the queue
    sem_wait(&queue->mutex);

    // Get the first node in the queue
    EventNode *curr = queue->head;

    // If the queue is empty return 0
    if (curr == NULL){
        sem_post(&queue->mutex);
        return 0;
    }
    
    // Store the veent data from the node
    *event = curr->event;
    // Update the head to the next head
    queue->head = curr->next;

    // Free the memory for the node we are removing
    free(curr);
    //Decrease the size
    queue->size--;
    sem_post(&queue->mutex);
    return 1;
}
