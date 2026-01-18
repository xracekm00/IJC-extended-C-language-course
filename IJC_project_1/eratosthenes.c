/**
 * @file eratosthenes.c
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad a)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "bitset.h"

//External function prototypes, so the code works with optimalisation turned off
#ifdef USE_INLINE
extern void bitset_free(bitset_t array_name);
extern bitset_index_t bitset_size(bitset_t array_name);
extern void bitset_fill(bitset_t array_name, bool bool_value);
extern void bitset_setbit(bitset_t array_name, bitset_index_t index, bool bool_value);
extern bool bitset_getbit(bitset_t array_name, bitset_index_t index);
#endif

void eratosthenes(bitset_t array){
    bitset_fill(array, true);               // Všetky prvky poľa okrem prvého (počet bitov) sú nastavené na 1
    bitset_index_t N = array[0];            // Získam veľkosť poľa (počet bitov)
    bitset_index_t limit = (bitset_index_t)ceil(sqrt((double)N));   // Nastavím limit na sqrt(N) a zaokrúhlim nahor

    // Ekvivalentne s klasickým eratosthenes algoritmom, kde v poli bitov nastavim [0] a [1] indexy na 0
    bitset_setbit(array, 0, false); // Nastavenie MSB bitu daneho cisla na 0.
    bitset_setbit(array, 1, false); // Nastavenie bitu za MSB daneho cisla na 0.

    for (bitset_index_t bit_count = 2; bit_count <= limit; bit_count++){
        /*
        *   V danom unsigned longu budem teraz prechádzat jednotlivými bitmi a pomocou bitovej aritmetiky
        *   budem porovnávať a meniť ich hodnotu podľa pravidiel algoritmu eratosthenovho syta.
        */
        if (bitset_getbit(array, bit_count)){
            for (bitset_index_t index = bit_count * bit_count; index < N; index += bit_count){
                bitset_setbit(array, index, false);
            }
        }
    }
}
