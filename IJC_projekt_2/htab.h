/**
 * @file    htab.h
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 2)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Include guards
#ifndef HTAB_H__
#define HTAB_H__

#include <string.h>
#include <stdbool.h>

// Hashtable data type - encapsulation 
struct htab;                                
typedef struct htab htab_t, *htab_ptr_t;  

// Types of variables each pair contains
typedef const char * htab_key_t;
typedef unsigned htab_value_t;

// Pair data type
typedef struct htab_pair {
    htab_key_t key;
    htab_value_t value;
} htab_pair_t, *htab_pair_ptr_t;

//Function prototypes

// If you create your own, this one won't be used -> compile using -DMY_HASH_FUNCTION
#ifndef MY_HASH_FUNCTION
size_t htab_hash_function(htab_key_t str);
#endif

// Functions for working with the hashtable
htab_ptr_t htab_init(size_t n);

// Functions to find out propperties of the hashtable
size_t htab_size(const htab_ptr_t h_table);
size_t htab_bucket_count(const htab_ptr_t h_table);

// Functions for using the hashtable
htab_pair_ptr_t htab_find(const htab_ptr_t h_table, htab_key_t key);
htab_pair_ptr_t htab_lookup_add(htab_ptr_t h_table, htab_key_t key);
// Deletes specific node
bool htab_erase(htab_ptr_t h_table, htab_key_t key);

/* Iterates through all the nodes and aplies function on each of them,
*  however it CAN NOT change 'key' nor 'add other members'
*/
void htab_for_each(const htab_ptr_t h_table, void (*f)(htab_pair_ptr_t data));

// Deletes all the nodes
void htab_clear(htab_ptr_t h_table);
// Frees memory
void htab_free(htab_ptr_t h_table);

#endif
