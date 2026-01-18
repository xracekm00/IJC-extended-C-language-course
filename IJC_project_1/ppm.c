/**
 * @file ppm.c
 * @author Martin Raček, xracekm00, FIT
 * @brief Riešenie IJC-DU1, príklad b)
 * @version 0.2
 * @date 2025-03-22
 * 
 * @details Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
 *          V tomto súbore zahŕňam funkciu zo zadania, ktorá kontroluje
 *          či je string v súlade s UTF-8 formátom. 
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "error.h"

/*
* Keďže mám dynamicky alokovať celú štuktúru a pole v nej ma formát ako lokálne pole na zásobníku
* tak použijem fintu z prednášky. Keď je pole umiestnené na konci structu a tomuto structu 
* naalokujeme pamäť vačšiu ako sú jeho položky, tak C sa bude tváriť, že táto pamäť prislúcha
* práve polu umiestnenemu na konci structu
*/

ptr_ppm_t ppm_read(const char * filename){
    //Openning the file stream
    FILE *file_ptr = fopen(filename, "rb");
    if (file_ptr == NULL){
        warning("ppm_read: Coudn't open file \"%s\"", filename);
        return NULL;
    }

    //Initial memory allocation for image
    ptr_ppm_t image = malloc(sizeof(ppm_t));
    if (image == NULL){
        warning("ppm_read: Memory allocation failed");
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Reading magic number
    if (fgetc(file_ptr) != 'P' || fgetc(file_ptr) != '6'){
        warning("ppm_read: Invalid PPM P6 format - expected a magic number P6");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Reading x and y sizes
    if (fscanf(file_ptr, "%u %u", &image->xsize, &image->ysize) != 2){
        warning("ppm_read: Invalid PPM P6 format - expected xsize, ysize");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Chceking if x and y are within a 16000 range
    if (image->xsize > MAX_RESOLUTION || image->ysize > MAX_RESOLUTION){
        warning("ppm_read: Invalid PPM P6 format - xsize or ysize bigger than implementation limit");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Reading color depth
    int colors;
    if (fscanf(file_ptr ,"%d", &colors) != 1 || colors != 255){
        warning("ppm_read: Invalid PPM P6 format - expected maximum color value (255)");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Reading '\n' character at the end of 255 (rgb colors max value)
    fgetc(file_ptr);

    //Reallocating memory for Image, so the data can be sotred
    image = realloc(image, sizeof(ppm_t) + (3 * image->xsize * image->ysize));
    if (image == NULL){
        warning("ppm_read: Memmory reallocation failed");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }
    
    //Reading the RGB data for each pixel
    if ((fread(image->data, sizeof(char), (3 * image->xsize * image->ysize), file_ptr)) != (3 * image->xsize * image->ysize)){
        warning("ppm_read: Failed to read image data");
        ppm_free(image);
        if (fclose(file_ptr)){
            warning("ppm_read: Coudn't close the file");
        }
        return NULL;
    }

    //Closing the file stream
    if (fclose(file_ptr)){
        warning("ppm_read: Coudn't close the file");
    }
    
    //Returns image
    return image;
}

void ppm_free(struct ppm *p){
    if (p != NULL)
    {
        free(p);
        p = NULL;
    }
}

/*
 * The utf8_check() function scans the '\0'-terminated string starting
 * at s. It returns a pointer to the first byte of the first malformed
 * or overlong UTF-8 sequence found, or NULL if the string contains
 * only correct UTF-8. It also spots UTF-8 sequences that could cause
 * trouble if converted to UTF-16, namely surrogate characters
 * (U+D800..U+DFFF) and non-Unicode positions (U+FFFE..U+FFFF). This
 * routine is very likely to find a malformed sequence if the input
 * uses any other encoding than UTF-8. It therefore can be used as a
 * very effective heuristic for distinguishing between UTF-8 and other
 * encodings.
 *
 * I wrote this code mainly as a specification of functionality; there
 * are no doubt performance optimizations possible for certain CPUs.
 *
 * Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/> -- 2005-03-30
 * License: http://www.cl.cam.ac.uk/~mgk25/short-license.html
 */

unsigned char *utf8_check(unsigned char *s){
    while (*s) {
        if (*s < 0x80)
            /* 0xxxxxxx */
            s++;
        else if ((s[0] & 0xe0) == 0xc0) {
            /* 110XXXXx 10xxxxxx */
        if ((s[1] & 0xc0) != 0x80 ||
        (s[0] & 0xfe) == 0xc0)                        /* overlong? */
            return s;
        else
            s += 2;
        } else if ((s[0] & 0xf0) == 0xe0) {
            /* 1110XXXX 10Xxxxxx 10xxxxxx */
        if ((s[1] & 0xc0) != 0x80 ||
        (s[2] & 0xc0) != 0x80 ||
        (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /* overlong? */
        (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate? */
        (s[0] == 0xef && s[1] == 0xbf &&
        (s[2] & 0xfe) == 0xbe))                      /* U+FFFE or U+FFFF? */
            return s;
        else
            s += 3;
        } else if ((s[0] & 0xf8) == 0xf0) {
            /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
        if ((s[1] & 0xc0) != 0x80 ||
        (s[2] & 0xc0) != 0x80 ||
        (s[3] & 0xc0) != 0x80 ||
        (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
        (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
            return s;
        else
            s += 4;
        } else
            return s;
    }
return NULL;
}
