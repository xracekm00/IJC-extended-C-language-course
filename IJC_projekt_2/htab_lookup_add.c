/**
 * @file    htab_lookup_add.c
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
 * @brief Increments value of already existing key or creates a new pair
 * 
 * @param h_table 
 * @param key 
 * @return htab_pair_ptr_t 
 */
htab_pair_ptr_t htab_lookup_add(htab_ptr_t h_table, htab_key_t key){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_lookup_add: null pointer passed as a function param\n");
        return NULL;
    }

    // Calculating index in the hash table
    size_t index = htab_hash_function(key) % h_table->arr_size;
    htab_pair_ptr_t found = htab_find((const htab_ptr_t)h_table, key);

    // When the key is already in the hash table
    if (found != NULL){
        found->value++;
        return found;
    }

    // Else, new node has to be created
    node_ptr_t new_node = malloc(sizeof(node_t));
    if (new_node == NULL){
        fprintf(stderr, "Error - htab_lookup_add: memory allocation failed\n");
        return NULL;
    }

    // Memory allocation for pair and key
    new_node->pair = malloc(sizeof(htab_pair_t));
    if (new_node->pair == NULL) {
        free(new_node);
        fprintf(stderr, "Error - htab_lookup_add: memory allocation failed\n");
        return NULL;
    }
    // Memory allocation for key
    new_node->pair->key = malloc((strlen(key) + 1) * sizeof(char));
    if (new_node->pair->key == NULL) {
        free(new_node);
        fprintf(stderr, "Error - htab_lookup_add: memory allocation failed\n");
        return NULL;
    }

    // Sets variables
    strcpy((char *)new_node->pair->key, key);
    new_node->pair->value = 1;
    new_node->next = NULL;

    // Inserting new node to the beginning of the list
    new_node->next = h_table->array_ptr[index];

    // Updating hashtable information
    h_table->array_ptr[index] = new_node;
    h_table->size++;

    return new_node->pair;
}
