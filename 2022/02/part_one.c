#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Day 2: Rock Paper Scissors
 * The input consists of two columns: the choice of your opponent, your choice
 *
 * The choice are abbreviated with letters:
 *   A, X: Rock
 *   B, Y: Paper
 *   C, Z: Scissors
 * 
 * c >= 'A' && c <= 'C' are the letters of your opponent
 * c >= 'X' && c <= 'Z' are your letters
 * */

int calculate_score(char a, char b) {
    int score = 0;

    /* base score: 1 for Rock, 2 for paper, 3 for scissors */
    score = b == 'X' ? 1 : b == 'Y' ? 2 : b == 'Z' ? 3 : 0;

    /* add 6 pts to the score if: Rock - Paper, Paper - Scis., Sciss. - Rock */
    if ((a == 'A' && b == 'Y') || (a == 'B' && b == 'Z') || (a == 'C' && b == 'X'))
        score += 6;
    /* add 3 pts to the score if: Rock - Rock, Paper - Paper, Sciss. - Sciss.*/
    else if((a == 'A' && b == 'X') || (a == 'B' && b == 'Y') || (a == 'C' && b == 'Z'))
        score += 3;

    return score;
}

int part_one() {
    FILE* file_ptr;

    file_ptr = fopen("input.txt", "r");
    if(!file_ptr)
        exit(EXIT_FAILURE);

    int player_score = 0;

    char col_a, col_b; /* letters in the columns of the current line */
    char c, last_c;    /* current character and last character */

    while((c = fgetc(file_ptr)) != EOF) {
        if(c == '\n') {
            player_score += calculate_score(col_a, col_b);
            col_a = col_b = 0;
        } else if((c >= 'A' && c <= 'C') || (c >= 'X' && c <= 'Z')) {
            if(last_c == ' ')
                col_b = c;
            else
                col_a = c;
        }

        if (c != '\r') /* ignore CR (Windows files) */
            last_c = c;
    }
    fclose(file_ptr);

    printf("What would your total score be if everything goes exactly according to your strategy guide? %d\n", player_score);
}

int main(int argc, char** argv) {
    part_one();
}