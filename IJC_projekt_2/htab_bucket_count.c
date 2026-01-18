/**
 * @file    htab_bucket_count.c
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

#include <stdio.h>

/**
 * @brief Returns how many different indices are in the hashtable
 * 
 * @param h_table 
 * @return size_t 
 */
size_t htab_bucket_count(const htab_ptr_t h_table){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_bucket_count: null pointer passed as a function param\n");
        return 0;
    }
    return h_table->arr_size;
}
