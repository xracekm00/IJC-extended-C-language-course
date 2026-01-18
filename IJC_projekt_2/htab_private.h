/**
 * @file    htab_private.h
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 2)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Include guards
#ifndef HTAB_PRIVATE_H__
#define HTAB_PRIVATE_H__

#include "htab.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Node data type
typedef struct node node_t, *node_ptr_t;
struct node{
    htab_pair_ptr_t pair;
    node_ptr_t next;
};

// Hashtable data type - full definition
struct htab{
    // size = ammount of nodes/pairs
    // arr_size = ammount of pointers - heads of linked list
    size_t size, arr_size;
    node_ptr_t array_ptr[];
};

#endif
