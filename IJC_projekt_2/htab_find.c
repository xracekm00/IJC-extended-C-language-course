/**
 * @file    htab_find.c
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
 * @brief Finds pair of specific value
 * 
 * @param h_table 
 * @param key 
 * @return htab_pair_ptr_t 
 */
htab_pair_ptr_t htab_find(const htab_ptr_t h_table, htab_key_t key){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_find: null pointer passed as a function param\n");
        return NULL;
    }

    // Calculating index in the hash table
    size_t index = htab_hash_function(key) % h_table->arr_size;
    node_ptr_t temp = h_table->array_ptr[index];

    // Iterating through linked list
    while (temp != NULL){
        if (strcmp(temp->pair->key, key) == 0){
            return temp->pair;
        }
        temp = temp->next;
    }
    
    // If no match was found
    return NULL;
}
