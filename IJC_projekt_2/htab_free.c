/**
 * @file    htab_free.c
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
 * @brief Destructor of hashtable
 * 
 * @param h_table 
 */
void htab_free(htab_ptr_t h_table){
    // Checking if the function parameters are valid
    if (h_table == NULL){
        fprintf(stderr, "Error - htab_free: null pointer passed as a function param\n");
        return;
    }
    // Cleaning memory
    htab_clear(h_table);
    free(h_table);

    return;
}
