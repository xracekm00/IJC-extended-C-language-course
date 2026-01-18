/**
 * @file steg-decode.c
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad b)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 *          Vypis zahrňuje informáciu, či je string v UTF-8 formáte.
 *          Momentálne je zakomentovaná na konci mainu.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bitset.h"
#include "ppm.h"
#include "error.h"

//Makes code more readable
#define START_PRIME 101

int main(int argc, char const *argv[])
{
    //Chceks if the program's input is valid
    if (argc < 2 || (strstr(argv[1], ".ppm") == NULL )){
        error_exit("steg-decode.c: Invalid argc or file name suffix: %s", argv[1]);
    }

    //Allocating and reading image
    ptr_ppm_t image = ppm_read(argv[1]);
    //Chceking if everything went as it was supposed to
    if (image == NULL){
        error_exit("steg-decode.c: Error occured while reading PPM P6");
    }

    //Creating array on which eratosthenes() will be executed
    bitset_t arr_prime_bytes;
    bitset_alloc(arr_prime_bytes, (3 * image->xsize * image->ysize) * 8);

    //Calling the eratothenes function
    eratosthenes(arr_prime_bytes);

    //Stores how many primes there are within the bounds
    bitset_index_t primes_count = 0;
    //Evaluating the ammount of primes
    for (bitset_index_t bit_count = START_PRIME; bit_count < arr_prime_bytes[0]; bit_count++){
        if (bitset_getbit(arr_prime_bytes, bit_count)){
            primes_count++;
        }
    }

    //Message max possible size
    bitset_index_t message_size = ((primes_count / 8) == 0) ? (primes_count / 8):(1 + (primes_count / 8));
    //Allocating memory for message
    unsigned char *message = calloc(message_size, sizeof(unsigned char));
    if (message == NULL){
        error_exit("steg-decode.c: Memory allocation failed");
    }

    //Helpfull variables
    unsigned char byte = 0;             // Index charu v message
    unsigned char bit_index = 0;        // 0000 0000 = bit v chare spravy
    unsigned char lsb = 1;              // 0000 0001 = maska
    unsigned char temp = 1;             // Pocita, ci som naplnil dany char (8b)

    //Prechadzam všetkými prvkami eratostenovho syta
    for (bitset_index_t byte_count = START_PRIME; byte_count < arr_prime_bytes[0]; byte_count++){
        //Ak je prvocislo
        if (bitset_getbit(arr_prime_bytes, byte_count)){
            //Pri každom novom if nulujem premennú
            temp = 1;     // 0000 0001
            
            if (((image->data[byte_count] & (lsb)) != 0)){
                message[byte] |= (temp << bit_index);
            }
            else{
                message[byte] &= ~(temp << bit_index);
            }
            bit_index++;
            //Po nastaveni vsetkch 8 bitov jedneho charu
            if (bit_index == 8){
                //Ak som nasiel \0 charakter, tak končím
                if (message[byte] == '\0'){
                    break;
                }
                bit_index = 0;
                byte++;
            }
        }
    }
    
    //Chceking if the message is null terminated
    bool is_null_terminated = false;
    for (unsigned char i = 0; i <= strlen((char *)message); i++){
        if (message[i] == '\0'){
            is_null_terminated = true;
        }   
    }

    //If not, error_exit() is called
    if (!is_null_terminated)
    {
        bitset_free(arr_prime_bytes);
        free(message);
        error_exit("steg-decode.c: Hidden message isn't null terminated");
    }

    //Chceking if the string has correct format
    /*
    if (utf8_check(message) != NULL){
        error_exit("The string isn't in UTF8 format: %s\n", message);
    }else{
        printf("Valid message format\n");
    }
    */
   
    //Printing the hidden message
    printf("%s\n", message);

    //Freeing memory
    bitset_free(arr_prime_bytes);
    free(message);
    ppm_free(image);

    return 0;
}