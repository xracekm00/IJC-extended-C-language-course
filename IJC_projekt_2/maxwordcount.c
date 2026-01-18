/**
 * @file    maxwordcount.c
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 2)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

/* Since the io.c module doesn't have a header file, 
*  extern function declaration will take care of it
*/
extern int read_word(unsigned max, char string[max], FILE * input_stream);

/* At first I chose DEFAULT_ARR_SIZE = 101 because its recommended to use prime numbers
*  so it's more convenient when using % operator to get an item index.
*  Also it was used in the book "Programovací jazyk C" by Kernighan and Ritchie, however
*  when I tried the programme on bigger range of words (some books) I found out that
*  having bigger array is more effective than having a longer list due to too manyindex 
*  colisions. So I'm using 503 now.
*/
#define DEFAULT_ARR_SIZE 12289
#define MAX_WORD_LEN 256

// Simple not so effective hash function I came up with
#ifdef MY_HASH_FUNCTION

size_t htab_hash_function(htab_key_t str){
    unsigned length = strlen(str);
    unsigned hash_value = 0;
    for (unsigned i = 0; i < length; i++){
        hash_value += str[i];
        hash_value *= str[i];
    }
    return hash_value;
}

#endif

// Global variable
unsigned max_occurance = 0;

// Function prototypes
void find_max(htab_pair_ptr_t data);
void print_max(htab_pair_ptr_t data);

// Type of: function pointer that returns nothing and takes one parameter of type htab_pair_ptr_t
typedef void (* htab_for_each_function_ptr)(htab_pair_ptr_t);

int main()
{
    // Creating a hash table
    htab_ptr_t hash_table = htab_init(DEFAULT_ARR_SIZE);
    if (hash_table == NULL){
        fprintf(stderr, "Error - maxwordcount: failed to initialize hash table\n");
        return EXIT_FAILURE;
    }
    
    /* It's unclear whether the input stream is expected to be a programme parameter,
    *  but C++ implementation has empty main, so I decided to use stdin
    */ 
    FILE *input_stream = stdin;
    
    // Allocating memory for input variable
    htab_key_t word = malloc(sizeof(char) * MAX_WORD_LEN);
    if (word == NULL){
        fprintf(stderr, "Error - maxwordcount.c: memory allocation failed\n");
        return EXIT_FAILURE;
    }
    // Stores return value - the length of word that is being processed
    int len;
    // Reading and adding lines into the hash table
    htab_pair_ptr_t return_pair;
    while ((len = read_word(MAX_WORD_LEN, (char *)word, input_stream)) != EOF){
        if (len > 0){
            return_pair = htab_lookup_add(hash_table, word);
            if (return_pair == NULL){
                htab_free(hash_table);
                fprintf(stderr, "Error - maxwordcount: failed to add word to hash table\n");
                return EXIT_FAILURE;
            }
        }
    }
    
    // Variables pointing to functions defined below
    htab_for_each_function_ptr find_max_ptr = find_max;
    htab_for_each_function_ptr print_max_ptr = print_max;

    // Finds keys with the biggest occurance
    htab_for_each((const htab_ptr_t)hash_table, find_max_ptr);
    // Print keys with the biggest occurance 
    htab_for_each((const htab_ptr_t)hash_table, print_max_ptr);
    
    // Cleaning the memory
    htab_free(hash_table);
    free((void *)word);

    // In case that I'll want to switch the input stream
    if (input_stream != stdin){
        fclose(input_stream);
    }

    return 0;
}

/**
 * @brief Finds which key in hashtable has the biggest occurance
 * 
 * @param data 
 */
void find_max(htab_pair_ptr_t data){
    if (data->value > max_occurance){
        max_occurance = data->value;
    }
}

/**
 * @brief Prints the words that has the highest occurance
 * 
 * @param data 
 */
void print_max(htab_pair_ptr_t data){
    if (data->value == max_occurance){
        printf("%s\t%u\n", data->key, data->value);
    }
}
