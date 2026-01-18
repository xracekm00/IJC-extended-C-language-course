/**
 * @file    htab_init.c
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

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Constructor for hashtable
 * 
 * @param n 
 * @return htab_ptr_t 
 */
htab_ptr_t htab_init(size_t n){
    // Check if n is valid
    if (n == 0) {
        fprintf(stderr, "Error - htab_init: array size must be greater than 0\n");
        return NULL;
    }

    // Allocating memory
    htab_ptr_t hash_table = malloc(sizeof(htab_t) + n * sizeof(node_ptr_t));
    if (hash_table == NULL){
        fprintf(stderr, "Error - htab_init: memory allocation failed\n");
        return NULL;
    }

    // Initializing variables
    hash_table->size = 0;
    hash_table->arr_size = n;

    for (size_t i = 0; i < n; i++){
        hash_table->array_ptr[i] = NULL;
    }

    return hash_table;
}
