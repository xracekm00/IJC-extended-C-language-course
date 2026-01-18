/**
 * @file    io.c
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 2)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

/**
 * @brief Reads word of a specific max length from input-stream
 * 
 * @param max 
 * @param string 
 * @param input_stream 
 * @return int 
 */
int read_word(unsigned max, char string[max], FILE * input_stream){
    // Checking if the function parameters are valid
    if (input_stream == NULL || string == NULL){
        fprintf(stderr, "Error - read_word: null pointer passed as a function param\n");
        return EOF;
    }
    if (max > MAX_WORD_LEN){
        fprintf(stderr, "Error - read_word: max word length is %d\n", MAX_WORD_LEN-1);
        return EOF;
    }
    
    // Static variable - hold its value until the programme is terminated
    static bool first_overflow = true;

    //Variables necessary for reading
    int letter;
    unsigned count = 0;

    // If the word preceeds with whitespaces
    while ((letter = fgetc(input_stream)) != EOF && isspace(letter)){
        ;
    }
    if (letter == EOF){
        return EOF;
    }

    // First non-whitespace character
    string[count] = letter;
    count++;

    // Reading one word
    while ((letter = fgetc(input_stream)) != EOF && !isspace(letter)){
        if (count < (max-1)){
            string[count] = letter;
            count++;
        }else{
            // If the word being read was longer than max
            if (first_overflow){
                fprintf(stderr, "Warning: word exceeds max length (255)\n");
                first_overflow = false;
            }
            // Skipping the rest of the characters
            while ((letter = fgetc(input_stream)) != EOF && !isspace(letter)){
                ;
            }
            break;
        }
    }
    // Making sure that the word is null terminated
    string[count] = '\0';
    
    return count;
}
