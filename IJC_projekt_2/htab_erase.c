/**
 * @file    htab_erase.c
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
 * @brief Deletes a node with pair with key value that
 *        matches the one passed as a parameter
 * 
 * @param h_table 
 * @param key 
 * @return true 
 * @return false 
 */
bool htab_erase(htab_ptr_t h_table, htab_key_t key){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_erase: null pointer passed as a function param\n");
        return false;
    }

    // Calculating index in the hash table
    size_t index = htab_hash_function(key) % h_table->arr_size;
    htab_pair_ptr_t temp_pair = htab_find((const htab_ptr_t) h_table, key);

    // When there isn't a pair with such key
    if (temp_pair == NULL){
        fprintf(stderr, "Error - htab_erase: key can not be erased because it doesn't exist\n");
        return false;
    }else{
        // Iterating through linked list
        node_ptr_t temp_node = h_table->array_ptr[index];
        node_ptr_t previous = NULL;
        while (strcmp(temp_node->pair->key, key) != 0){
            previous = temp_node;
            temp_node = temp_node->next;
        }

        // When the node that's being erased is the first
        if (previous == NULL){
            h_table->array_ptr[index] = temp_node->next;
        }
        // When the node that's being erased is the last
        else if (temp_node->next == NULL){
            previous->next = NULL;
        }else{
            previous->next = temp_node->next;
        }

        // Cleaning memory and updating hashtable info
        free((void *)temp_node->pair->key);
        free(temp_node->pair);
        free(temp_node);
        h_table->size--;

        return true;
    }
}
