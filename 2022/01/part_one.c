#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one() {
    FILE* file_ptr;

    file_ptr = fopen("input.txt", "r");
    if(!file_ptr)
        exit(EXIT_FAILURE);

    int max_calories = 0; /* elf with the most calories*/
    int current_elf = 0;  /* sum of calories of current elf */
    char buffer[10] = ""; /* buffer to store digits */
    char c, last_c;       /* current character and last character */
    int i = 0;            /* track position of digit */

    while((c = fgetc(file_ptr)) != EOF) {
        if(c == '\n') {
            /* when a newline is encountered, the digits stored in buffer get
             * converted into an int and stored in current_elf */
            current_elf += atoi(buffer);
            memset(buffer, 0, 10); /* empty buffer for next line */
            i = 0;

            /* when a newline is followed by a newline, move on to the next elf */
             if(last_c == '\n') {
                if(current_elf > max_calories)
                    max_calories = current_elf;
                current_elf = 0;
            }
        } else if(c >= '0' && c <= '9')
        /* store digits in buffer until newline is encountered*/
            buffer[i++] = c;

        if (c != '\r') /* ignore CR (Windows files) */
            last_c = c;
    }
    fclose(file_ptr);

    printf("Find the Elf carrying the most Calories. How many total Calories is that Elf carrying? %d\n", max_calories);
}

int main(int argc, char** argv) {
    part_one();
}