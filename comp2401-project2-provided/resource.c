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
   
    if (resource == NULL || name == NULL){
        return;
    }

    *resource = malloc(sizeof(Resource));

    (*resource)->name = calloc(sizeof(name)/sizeof(char), sizeof(char));
    
    strcpy((*resource) ->name, name -1);

    (*resource)->amount = amount;
    (*resource)->max_capacity = max_capacity;

}

/**
 * Destroys a `Resource` object.
 *
 * Frees all memory associated with the `Resource`.
 *
 * @param[in,out] resource  Pointer to the `Resource` to be destroyed.
 */
void resource_destroy(Resource *resource) {

    if (resource!=NULL){
        free(resource->name);
        free(resource);
    }
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
    for(int i = 0; i<array->size;i++){
        resource_destroy(array->resources[i]);
    }

    free(array->resources);
    array->capacity = 0;
    array->size = 0;
   
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
    
    if (array->size >= array->capacity){
        // Temp to store memory if needed
        Resource *temp;

        // New memory with space for 2 times more resources
        temp = calloc((array->capacity)*2,sizeof(Resource));

        // Copy existing resources to new memory
        for (int i = 0; i < array->size;i++){
                temp[i] = *array->resources[i];
        }
        // Free the old memory
        resource_array_clean(array);

        // Updates array to point to the new memory of resources
        *array->resources = temp;
        
        array->capacity = array->capacity*2;
    }

    array->resources[array->size] = resource;
    array->size++;
    

}