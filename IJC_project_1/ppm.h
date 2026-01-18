/**
 * @file ppm.h
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
#ifndef PPM_H
#define PPM_H

//Makes code more readable
#define MAX_RESOLUTION 16000
#define RGB 255

//Struct to store the information necessary about the picture
typedef struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
}ppm_t, *ptr_ppm_t;

//Function prototypes
struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);
unsigned char *utf8_check(unsigned char *s);

#endif