/**
 * @file    tail.c
 * @author  Martin Raček, xracekm00, FIT
 * @brief   Riešenie IJC-DU2, príklad 1)
 * @version 0.1
 * @date    2025-04-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Helpful constants
#define DEFAULT_COUNT 10
#define MAX_LINE_LEN 4096

// Circular buffer data type
typedef struct{
    char** lines;
    unsigned long start, end, entries, max_elements;
} tCbuf, *tCbufPtr;

//Function prototypes
tCbufPtr cbuf_create(unsigned long count);
void cbuf_free(tCbufPtr circular_buffer);

bool cbuf_put(tCbufPtr circular_buffer, char *line);
char *cbuf_get(tCbufPtr circular_buffer);

bool read_lines(tCbufPtr circular_buffer, FILE *input_stream);
void print_lines(tCbufPtr circular_buffer);

//Two macro-like functions used for boundary checking
#define que_full(circular_buffer) \
    (circular_buffer)->entries == (circular_buffer)->max_elements

#define que_empty(circular_buffer) \
    (circular_buffer)->entries == 0

int main(int argc, char const *argv[])
{
    /* How the programme can be started?
    *   ./tail           ~    ./tail <file
    * 
    *   ./tail -n 123    ~    ./tail -n 123 <file
    *     
    *   ./tail file      ~    ./tail -n 123 file
    */

    if (argc >= 5){
        fprintf(stderr, "Error - tail.c: too many arguments\n");
        return EXIT_FAILURE;
    }
    
    // If argc = 1, variables are set
    unsigned long lines_count = DEFAULT_COUNT;
    FILE *input_stream = stdin;

    // Other ways to start the programme
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        // ./tail -n
        if (argc < 3) {
            fprintf(stderr, "Error - tail.c: Missing number after -n\n");
            return EXIT_FAILURE;
        }
        // ./tail -n -negative_nb
        if (argv[2][0] == '-') {
            fprintf(stderr, "Error - tail.c: Invalid -n 'number of lines' specifier\n");
            return EXIT_FAILURE;
        }
        // ./tail -n 123abc
        // ./tail -n abc
        char *endptr;
        lines_count = strtoul(argv[2], &endptr, 10);
        if (endptr[0] != '\0' || strcmp(argv[2], "\0") == 0) {
            fprintf(stderr, "Error - tail.c: Invalid -n 'number of lines' specifier\n");
            return EXIT_FAILURE;
        }
    }

    // When lines count is 0 -> nothing will happen
    if (lines_count == 0){
        return EXIT_SUCCESS;
    }

    // When the input is a content of another file
    if (argc == 2 && strcmp(argv[1], "-n") != 0) {
        input_stream = fopen(argv[1], "r");
    } else if (argc == 4 && !strcmp(argv[1], "-n") != 0) {
        input_stream = fopen(argv[3], "r");
    }
    // If the file-stream was openned unsuccessfuly
    if (input_stream == NULL) {
        fprintf(stderr, "Error - tail.c: Coudn't open a file\n");
        return EXIT_FAILURE;
    }

    // Calling functions working with circular buffer

    // Creating circular buffer
    tCbufPtr circ_buff_1 = cbuf_create(lines_count);
    if (circ_buff_1 == NULL){
        if (input_stream != stdin) fclose(input_stream);
        return EXIT_FAILURE;
    }

    // Filling the circullar buffer with last 10 lines of input
    bool return_value;
    return_value = read_lines(circ_buff_1, input_stream);
    if (!return_value){
        cbuf_free(circ_buff_1);
        if (input_stream != stdin) fclose(input_stream);
        return EXIT_FAILURE;
    }
    
    // Printing the lines
    print_lines(circ_buff_1);
    // printf("\n");

    // Cleaning the used memory
    cbuf_free(circ_buff_1);

    // If the input wasn't from stdin, file-stream has to be closed
    if (input_stream != stdin) {
        fclose(input_stream);
    }

    return 0;
}

/**
 * @brief Constructor for circular buffer
 * 
 * @param count ;amount of lines to search for
 * @return tCbufPtr
 */
tCbufPtr cbuf_create(unsigned long count){
    // Allocating memory for the buffer
    tCbufPtr queue = malloc(sizeof(tCbuf));
    if (queue == NULL){
        fprintf(stderr, "Error - cbuf_create: memory allocation failed\n");
        return NULL;
    }
    
    // Allocating memory for char **lines
    queue->lines = malloc(count * sizeof(char *));
    if (queue->lines == NULL){
        free(queue);
        fprintf(stderr, "Error - cbuf_create: memory allocation failed\n");
        return NULL;
    }
    
    // Initialization of variables
    queue->entries = 0;
    queue->start = 0;
    queue->end = 0;
    queue->max_elements = count;

    for (unsigned long i = 0; i < count; i++){
        queue->lines[i] = NULL;
    }
    

    return queue;
}

/**
 * @brief Destructor for circular buffer
 * 
 * @param circular_buffer 
 */
void cbuf_free(tCbufPtr circular_buffer){
    // Checks the parameter
    if (circular_buffer == NULL){
        fprintf(stderr, "Error - cbuf_free: null pointer passed as a function param\n");
        return;
    }
    
    // Cleaning the memory
    for (unsigned long i = 0; i < circular_buffer->max_elements; i++){
        if (circular_buffer->lines[i] != NULL){
            free(circular_buffer->lines[i]);
            circular_buffer->lines[i] = NULL;
        }
    }
    free(circular_buffer->lines);
    circular_buffer->lines = NULL;
    free(circular_buffer);
    circular_buffer = NULL;
}

/**
 * @brief Allocates memory for and inserts line into the circular buffer
 * 
 * @param circular_buffer 
 * @param line 
 * @return true 
 * @return false 
 */
bool cbuf_put(tCbufPtr circular_buffer, char *line){
    // Checks the parameters
    if (circular_buffer == NULL || line == NULL){
        fprintf(stderr, "Error - cbuf_put: null pointer passed as a function param\n");
        return false;
    }

    // When the buffer is full, the start index has to be advanced
    if (que_full(circular_buffer)){
        free(circular_buffer->lines[circular_buffer->start]);
        circular_buffer->lines[circular_buffer->start] = NULL;
        circular_buffer->start = (circular_buffer->start + 1) % circular_buffer->max_elements;
        circular_buffer->entries--;
    }

    
    // Whether the line exceeds the MAX_LINE_LEN etc is taken care of in read_line function.

    // Allocating memory for the line
    circular_buffer->lines[circular_buffer->end] = malloc((strlen(line) + 1) * sizeof(char));
    if (circular_buffer->lines[circular_buffer->end] == NULL){
        fprintf(stderr, "Error - cbuf_put: memory allocation failed\n");
        return false;
    }
    // Storing the line to the cir. buffer.
    strcpy(circular_buffer->lines[circular_buffer->end], line);
    circular_buffer->end = (circular_buffer->end + 1) % circular_buffer->max_elements;
    circular_buffer->entries++;

    return true;
}

/**
 * @brief Function similar to POP - return string stored at the end of circular buffer
 *        and cleans memory
 * 
 * @details caller has to free the memory of returned string
 * 
 * @param circular_buffer 
 * @return char* 
 */
char *cbuf_get(tCbufPtr circular_buffer){
    // Checks the parameter
    if (circular_buffer == NULL){
        fprintf(stderr, "Error - cbuf_get: null pointer passed as a function param\n");
        return NULL;
    }
    // When que is empty, there's nothing to return
    if (que_empty(circular_buffer))
    {
        fprintf(stderr, "Error - cbuf_get: can't read when the buffer is empty\n");
        return NULL;
    }

    // Allocating memory for the return pointer
    char *temp = malloc((strlen(circular_buffer->lines[circular_buffer->start]) + 1) * sizeof(char));
    if (temp == NULL){
        fprintf(stderr, "Error - cbuf_get: memory allocation failed\n");
        return NULL;
    }
    
    // Copying the content into the return pointer and cleaning memory
    strcpy(temp, circular_buffer->lines[circular_buffer->start]);
    free(circular_buffer->lines[circular_buffer->start]);
    circular_buffer->lines[circular_buffer->start] = NULL;
    circular_buffer->start = (circular_buffer->start + 1) % circular_buffer->max_elements;
    circular_buffer->entries--;

    return temp;
}

/**
 * @brief Reads line from the input stream to the end of circular buffer 
 * 
 * @param circular_buffer 
 * @param input_stream 
 * @return true 
 * @return false 
 */
bool read_lines(tCbufPtr circular_buffer, FILE *input_stream){
    // Checks the parameters
    if (circular_buffer == NULL || input_stream == NULL){
        fprintf(stderr, "Error - read_lines: null pointer passed as a function param\n");
        return false;
    }

    // Variables necessary for reading the line
    char temp[MAX_LINE_LEN];
    int bin;
    bool first_exceed = true;

    // Reading
    while (fgets(temp, MAX_LINE_LEN, input_stream)){
        // It never happened to me, but just in case that there was error while reading
        if (ferror(input_stream)){
            fprintf(stderr, "Error - read_lines: reading inout failed\n");
            return false;
        }

        // Stores the line into buffer
        if (!cbuf_put(circular_buffer, temp)){
            fprintf(stderr, "Error - read_lines: problem encountered while reading lines\n");
            return false;
        }

        // When the line has more characters than it's supposed to
        if (strchr(temp, '\n') == NULL && !feof(input_stream)){
            if (first_exceed){
                // Warning - read_lines: line exceeds max amount of characters\n
                fprintf(stderr, "Warning: line exceeds max amount of characters (4094)\n");
                first_exceed = false;
            }
            // Skipping the rest of the line
            while ((bin = fgetc(input_stream)) != '\n' && bin != EOF){
                ;
            }
        }
    }

    return true;
}


/**
 * @brief Prints the content of the circular buffer
 * 
 * @param circular_buffer 
 */
void print_lines(tCbufPtr circular_buffer) {
    // Checks the parameters
    if (!circular_buffer) {
        fprintf(stderr, "Error - print_lines: null pointer passed as a function param\n");
        return;
    }

    // Reading and printing the lines
    char *temp = NULL;
    while (!que_empty(circular_buffer)) {
        temp = cbuf_get(circular_buffer);
        if (!temp) {
            fprintf(stderr, "Error - print_lines: problem encountered while printing lines\n");
            return;
        }
        printf("%s", temp);
        // cbuf_get needs caller to clean the memory used by its returned pointer
        free(temp);
    }

    return;
}
