/**
 * @file    htab_clear.c
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 2)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "htab_private.h"
#include "htab.h"

/**
 * @brief Resets the hashtable array
 * 
 * @param h_table 
 */
void htab_clear(htab_ptr_t h_table){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_clear: null pointer passed as a function param\n");
        return;
    }

    // Iterating through each node of linked list
    node_ptr_t temp, next;
    for (size_t i = 0; i < h_table->arr_size; i++) {
        temp = h_table->array_ptr[i];

        while (temp != NULL) {
            next = temp->next;

            free((void *)temp->pair->key);
            free(temp->pair);
            free(temp);

            temp = next;
        }
        h_table->array_ptr[i] = NULL;
    }
    // Updating hashtable information
    h_table->size = 0;

    return;
}
