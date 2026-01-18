/**
 * @file primes.c
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad b)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 *          V progame používam pole uložené na zásobníku.
 *          Efektivita výpočtu: cca 2.2s -O2, 5s bez opt.
 *          Komponenty: AMD Ryzen 7 8845HS w/ Radeon 780M Graphics 3.80 GHz 32,0 GB RAM
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <time.h>
#include "bitset.h"
#include "error.h"

//Makes code more readable
#define NUMBER 333000000
#define PRIMES_SIZE 10

//External function prototypes, so the code works with optimalisation turned off
#ifdef USE_INLINE
extern void bitset_free(bitset_t array_name);
extern bitset_index_t bitset_size(bitset_t array_name);
extern void bitset_fill(bitset_t array_name, bool bool_value);
extern void bitset_setbit(bitset_t array_name, bitset_index_t index, bool bool_value);
extern bool bitset_getbit(bitset_t array_name, bitset_index_t index);
#endif

int main()
{
    //Taking the first measurement of time
    clock_t start = clock();

    //Creating array
    bitset_t array;
    bitset_create(array, NUMBER);
    
    //Calling eratosthenes function
    eratosthenes(array);

    //Storing the bit size of the array
    bitset_index_t N = array[0];
    
    //Temporary variables to print the corrseponding values
    bitset_index_t primes_array[PRIMES_SIZE] = {0};
    bitset_index_t temp = PRIMES_SIZE - 1;

    //Filling the temp array with desired output values
    int count;
    bitset_index_t j;
    for (count = PRIMES_SIZE, j = N-1; j >= 2 && count > 0; j--){
        if (bitset_getbit(array, j)){
           primes_array[temp] = j;
           temp--;
           count--;
        }
    }

    //Printing the output values
    for (bitset_index_t i = 0; i < 10 && primes_array[i]; i++){
        printf("%lu\n", primes_array[i]);
    }
    
    //Taking the last measurement of time and printing how long it took to execute
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    //bitset_free(array);

    return 0;
}