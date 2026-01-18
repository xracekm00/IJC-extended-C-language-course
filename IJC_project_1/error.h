/**
 * @file error.h
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

//Include guards
#ifndef ERROR_H
#define ERROR_H

//Function prototypes
void warning(const char *format, ...);
void error_exit(const char *format, ...);

#endif