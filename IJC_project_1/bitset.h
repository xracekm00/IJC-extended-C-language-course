/**
 * @file bitset.h
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad a)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 *          bitset_t pole deklarujem v maine, funkcie ho definujú a inicializujú.
 *          Funguje pre rovnakú premennú bitset_create(pole), bitset_alloc(pole).
 *          Nefunguje mi static bitset_create(pole).
 * 
 * @copyright Copyright (c) 2025
 * 
 */

//Libraries mutual for most modules
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "error.h"

//include guards
#ifndef BITSET_H
#define BITSET_H

//type of bit array
typedef unsigned long *bitset_t;
//type of bit array index
typedef unsigned long bitset_index_t;

//Function prototype so it can be used in primes.c f.e.
void eratosthenes(bitset_t);

//Makes code more readable
#define UL_BIT_SIZE (sizeof(unsigned long) * 8)
#define UL_BYTE_SIZE (sizeof(unsigned long))

//Creates and initiates array on stack
#define bitset_create(array_name, array_size) \
do { \
    static_assert(((array_size) > 0 && (array_size < SIZE_MAX)), "bitset_create: Velikost pole musi byt kladna"); \
    static unsigned long array_name##_local[(((array_size) / UL_BIT_SIZE) + 1 + ((array_size) % UL_BIT_SIZE != 0))] = {(array_size), 0}; \
    (array_name) = array_name##_local; \
} while (0)

//Creates and initiates array on heap
#define bitset_alloc(array_name, array_size) \
    do{ \
        assert((array_size) > 0 && (array_size <= SIZE_MAX)); \
        array_name = (bitset_t)calloc(((array_size) / UL_BIT_SIZE) + 1 + ((array_size) % UL_BIT_SIZE != 0), UL_BYTE_SIZE); \
        if (array_name == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); \
        array_name[0] = (array_size); \
    } while (0)

#ifdef USE_INLINE

    //Frees memmory used by dynammicly allocated array
    inline void bitset_free(bitset_t array_name){
        if (array_name != NULL){
            free((array_name));
            array_name = NULL;
        }
    }

    //Returns how many bits can be stored in array
    inline bitset_index_t bitset_size(bitset_t array_name){
        return array_name[0];
    }

    //Sets all bits, exept the ones from array[0], to 0's or 1's
    inline void bitset_fill(bitset_t array_name, bool bool_value){
        bitset_index_t size_in_longs = ((array_name[0] / UL_BIT_SIZE) + 1 + (array_name[0] % UL_BIT_SIZE != 0));
        for (bitset_index_t i = 1; i < size_in_longs; i++){
            if (bool_value){
                array_name[i] = -1; 
            }
            else{
                array_name[i] = 0UL;
            }
        }
    }

    //Sets specific bit, exept the ones from array[0], to 0 or 1
    inline void bitset_setbit(bitset_t array_name, bitset_index_t index, bool bool_value){
        if (index >= array_name[0]){
            error_exit("inline_bitset_setbit: Index %lu mimo rozsah 0..%lu", index, array_name[0]-1);
        }

        bitset_index_t item = ((index) / UL_BIT_SIZE) + 1;
        bitset_index_t bit = (index) % UL_BIT_SIZE;
        bitset_index_t temp = 1UL << bit;

        if (bool_value) {
            array_name[item] |= temp;
        }
        else {
            array_name[item] &= ~temp;
        }
    }

    //Returns value of specific bit
    inline bool bitset_getbit(bitset_t array_name, bitset_index_t index){
        if (index >= array_name[0]){
            error_exit("inline_bitset_getbit: Index %lu mimo rozsah 0..%lu", index, array_name[0]-1);
        }

        bitset_index_t item = ((index) / UL_BIT_SIZE) + 1;
        bitset_index_t bit = (index) % UL_BIT_SIZE;
        bitset_index_t temp = 1UL << bit;

        return ((array_name[item] & temp) != 0);
    }

#else

//Frees memmory used by dynammicly allocated array
#define bitset_free(array_name) \
    do{ \
        free((array_name)); \
        (array_name) = NULL; \
    } while (0)

//Returns how many bits can be stored in array
#define bitset_size(array_name) \
    ((array_name)[0])

//Sets all bits, exept the ones from array[0], to 0's or 1's
#define bitset_fill(array_name, bool_value) \
    do{ \
        bitset_index_t size_in_longs = (((array_name)[0] / UL_BIT_SIZE) + (((array_name)[0] % UL_BIT_SIZE) != 0)); \
        ((bool_value) ? (memset((array_name) + 1, -1, size_in_longs * UL_BYTE_SIZE)) : (memset((array_name) + 1, 0, size_in_longs * UL_BYTE_SIZE))); \
    } while (0)

//Sets specific bit, exept the ones from array[0], to 0 or 1
//(index) < 0 ||
#define bitset_setbit(array_name, index, bool_value) \
    do { \
        if ((index) >= (array_name)[0]){ \
            (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (index), ((array_name)[0]-1))); \
        } \
        bitset_index_t item = (index) / UL_BIT_SIZE; \
        bitset_index_t index_in_item = (index) % UL_BIT_SIZE; \
        bitset_index_t temp = 1UL << (index_in_item); \
        \
        if ((bool_value)) { \
            (array_name)[(item) + 1] |= temp; \
        } \
        else { \
            (array_name)[(item) + 1] &= ~temp; \
        } \
    } while (0); \

//Returns value of specific bit
//|| (index) < 0
#define bitset_getbit(array_name, index) \
( \
    ((index) >= (array_name)[0]) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (index), ((array_name)[0]-1))), 0 : 1, \
    (((array_name)[((index)/UL_BIT_SIZE) + 1] & (1UL << ((index) % UL_BIT_SIZE))) != 0) \
)

#endif

#endif
