/**
 * @file    htab_for_each.c
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
 * @brief Applies function passed as a parameter on each pair in hashtable
 * 
 * @details Can not alter the content of hashtable
 * 
 * @param h_table 
 * @param f 
 */
void htab_for_each(const htab_ptr_t h_table, void (*f)(htab_pair_ptr_t data)){
    // Checking if the function parameters are valid
    if (h_table == NULL || f == NULL){
        fprintf(stderr, "Error - htab_for_each: null pointer passed as a function param\n");
        return;
    }

    // Variables to keep track whether any change has been done
    node_ptr_t temp_node;
    htab_key_t key_backup;
    size_t node_count;

    // Applying the function onto each pair
    for (size_t i = 0; i < h_table->arr_size; i++){
        temp_node = h_table->array_ptr[i];
        while (temp_node != NULL){
            // Making backups to check whethet the function changed smth
            key_backup = malloc(sizeof(char) * (strlen(temp_node->pair->key) + 1));
            if (key_backup == NULL){
                fprintf(stderr, "Error - htab_for_each: memory allocation failed\n");
                return;
            }
            strcpy((char *)key_backup, temp_node->pair->key);
            node_count = h_table->size;

            f(temp_node->pair);
            
            // When change was detected
            if (node_count != h_table->size || strcmp(key_backup, temp_node->pair->key) != 0){
                free((void *)key_backup);
                fprintf(stderr, "Error - htab_for_each: invalid function that changes content of hashtable\n");
                return;
            }
            // Cleaning used memory
            free((void *)key_backup);

            // Advancing to the next node
            temp_node = temp_node->next;
        }
    }
    return;
}
