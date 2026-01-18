/**
 * @file error.c
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad b)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

//Variadic function for printing warnings
void warning(const char *format, ...){
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

//Variadic function for printing errors, terminates programme
void error_exit(const char *format, ...){
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(EXIT_FAILURE);
}
