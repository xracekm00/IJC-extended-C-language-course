/**
 * @file    htab_hash_function.c
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
#include <stdint.h>

#include "htab.h"

/**
 * @brief SBDM hash function
 * 
 * @details This function is specified by the task, however in the
 *          attached link, this function has a little different definition,
 *          but I used the one from the task, just in case.
 * 
 * @param str 
 * @return size_t 
 */
size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 0;
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
