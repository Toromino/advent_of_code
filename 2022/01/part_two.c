#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_two() {
    FILE* file_ptr;

    file_ptr = fopen("input.txt", "r");
    if(!file_ptr)
        exit(EXIT_FAILURE);

    int result, first, second, third;
    /* result: sum of top three elfs
     * first, second, third: calories of the top three elfs  */

    int current_elf = 0;  /* sum of calories of current elf */
    char buffer[10] = ""; /* buffer to store digits */
    char c, last_c;       /* current character and last character */
    int i = 0;            /* track position of digit */

    result = first = second = third = 0;
    while((c = fgetc(file_ptr)) != EOF) {
        if(c == '\n') {
            /* when a newline is encountered, the digits stored in buffer get
             * converted into an int and stored in current_elf */
            current_elf += atoi(buffer);
            memset(buffer, 0, 10); /* empty buffer for next line */
            i = 0;

            /* when a newline is followed by a newline, move on to the next elf */
            if(last_c == '\n') {
                /* find out if the current elf belongs into the top three 
                -> algorithm: find the largest three distinct sums of calories */
                if(current_elf > first) {
                    third = second;
                    second = first;
                    first = current_elf;
                } else if(current_elf > second && current_elf != first) {
                    third = second;
                    second = current_elf;
                } else if(current_elf > third && current_elf != second)
                    third = current_elf;
                
                current_elf = 0; /* clear calorie count of current elf*/
            }
        } else if(c >= '0' && c <= '9')
         /* store digits in buffer until newline is encountered*/
            buffer[i++] = c;

        if (c != '\r') /* ignore CR (Windows files) */
            last_c = c;
    }
    fclose(file_ptr);

    result = first + second + third;
    printf("Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total? %d\n", result);
}

int main(int argc, char** argv) {
    part_two();
}