#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Resource functions */

/**
 * Creates a new `Resource` object.
 *
 * Allocates memory for a new `Resource` and initializes its fields.
 * The `name` is dynamically allocated.
 *
 * @param[out] resource      Pointer to the `Resource*` to be allocated and initialized.
 * @param[in]  name          Name of the resource (the string is copied).
 * @param[in]  amount        Initial amount of the resource.
 * @param[in]  max_capacity  Maximum capacity of the resource.
 */
void resource_create(Resource **resource, const char *name, int amount, int max_capacity) {
    // Allocate memory for Resouce and initialize all the values
    *resource = malloc(sizeof(Resource));
    (*resource)->name = malloc(strlen(name) + 1);
    strcpy((*resource)->name, name);
    (*resource)->amount = amount;
    (*resource)->max_capacity = max_capacity;
    sem_init(&(*resource)->mutex,0,1);
}

/**
 * Destroys a `Resource` object.
 *
 * Frees all memory associated with the `Resource`.
 *
 * @param[in,out] resource  Pointer to the `Resource` to be destroyed.
 */
void resource_destroy(Resource *resource) {
    sem_destroy(&resource->mutex);
    free(resource->name);
    free(resource);
}

/* ResourceAmount functions */

/**
 * Initializes a `ResourceAmount` structure.
 *
 * Associates a `Resource` with a specific `amount`.
 *
 * @param[out] resource_amount  Pointer to the `ResourceAmount` to initialize.
 * @param[in]  resource         Pointer to the `Resource`.
 * @param[in]  amount           The amount associated with the `Resource`.
 */
void resource_amount_init(ResourceAmount *resource_amount, Resource *resource, int amount) {
    resource_amount->resource = resource;
    resource_amount->amount = amount;
}

/**
 * Initializes the `ResourceArray`.
 *
 * Allocates memory for the array of `Resource*` pointers and sets initial values.
 *
 * @param[out] array  Pointer to the `ResourceArray` to initialize.
 */
void resource_array_init(ResourceArray *array) {
    array->resources = calloc(1,sizeof(Resource));
    array->size = 0;
    array->capacity = 1;

}

/**
 * Cleans up the `ResourceArray` by destroying all resources and freeing memory.
 *
 * Iterates through the array, calls `resource_destroy` on each `Resource`,
 * and frees the array memory.
 *
 * @param[in,out] array  Pointer to the `ResourceArray` to clean.
 */
void resource_array_clean(ResourceArray *array) {
    // Traverse thorugh each system in the array and clean the resources
    for (int i = 0; i < array->size; i++) {
        resource_destroy(array->resources[i]);
    }

    // Free the memory allocated for the array
    free(array->resources);
    array->resources = NULL;
    array->size = 0;
    array->capacity = 0;

}

/**
 * Adds a `Resource` to the `ResourceArray`, resizing if necessary (doubling the size).
 *
 * Resizes the array when the capacity is reached and adds the new `Resource`.
 * Use of realloc is NOT permitted.
 * 
 * @param[in,out] array     Pointer to the `ResourceArray`.
 * @param[in]     resource  Pointer to the `Resource` to add.
 */
void resource_array_add(ResourceArray *array, Resource *resource) {

    // Check if array needs resizing
    if (array->size >= array->capacity) {

        // Allocate memory for a new array with double the capacity
        Resource **temp;
        temp = calloc(array->capacity*2,sizeof(Resource));
    
        // Copy the existing systems from the old array to the new array
        for (int i = 0; i < array->size; ++i) {
            temp[i] = array->resources[i];
        }

        // Free the memory for the old array and updates the pointer to the new array
        free(array->resources);
        array->resources = temp;
        // Update the capacity to the new capacity 
        array->capacity = array->capacity * 2;
    }
    // Add the new system to the array 
    array->resources[array->size] = resource;
    // Increase the size
    array->size++;

}