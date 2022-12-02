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
 */

#define OPPONENT_ROCK     'A'
#define OPPONENT_PAPER    'B'
#define OPPONENT_SCISSORS 'C'

#define PLAYER_ROCK       'X'
#define PLAYER_PAPER      'Y'
#define PLAYER_SCISSORS   'Z'

/* Calculate your player's total score*/
unsigned int calculate_score(char a, char b) {
    unsigned int score = 0;

    /* base score: 1 for Rock, 2 for paper, 3 for scissors */
    score = b == PLAYER_ROCK     ? 1
          : b == PLAYER_PAPER    ? 2
          : b == PLAYER_SCISSORS ? 3
          : 0;

    /* add 6 pts to the score if: Rock - Paper, Paper - Scis., Sciss. - Rock */
    if ((a == OPPONENT_ROCK     && b == PLAYER_PAPER) ||
        (a == OPPONENT_PAPER    && b == PLAYER_SCISSORS) ||
        (a == OPPONENT_SCISSORS && b == PLAYER_ROCK)) {
        score += 6;
    }
    /* add 3 pts to the score if: Rock - Rock, Paper - Paper, Sciss. - Sciss.*/
    else if ((a == OPPONENT_ROCK     && b == PLAYER_ROCK) ||
             (a == OPPONENT_PAPER    && b == PLAYER_PAPER) ||
             (a == OPPONENT_SCISSORS && b == PLAYER_SCISSORS)) {
        score += 3;
    }

    return score;
}

/* For part two: Figure out what shape to choose so the round ends as indicated
 * by the second column.
 *
 * a: first column, b: second column
 */
char strategic_response(char a, char b) {
    if (b == 'X') {
        /* Needs to lose: Rock -> Scissors, Paper -> Rock, Scissors -> Paper*/
        return a == OPPONENT_ROCK     ? PLAYER_SCISSORS
             : a == OPPONENT_PAPER    ? PLAYER_ROCK
             : a == OPPONENT_SCISSORS ? PLAYER_PAPER
             : 0;
    } else if (b == 'Y') {
        /* needs a draw: Rock -> Rock, Paper -> Paper, Scissors -> Scissors*/
        return a == OPPONENT_ROCK     ? PLAYER_ROCK
             : a == OPPONENT_PAPER    ? PLAYER_PAPER
             : a == OPPONENT_SCISSORS ? PLAYER_SCISSORS
             : 0;
    } else if (b == 'Z') {
        /* needs to win: Rock -> Paper, Paper -> Scissors, Scissors -> Rock*/
        return a == OPPONENT_ROCK     ? PLAYER_PAPER
             : a == OPPONENT_PAPER    ? PLAYER_SCISSORS
             : a == OPPONENT_SCISSORS ? PLAYER_ROCK
             : 0;
    }
}

void part_two() {
    FILE *file_ptr;
    unsigned int player_score = 0;
    char col_a, col_b; /* letters in the columns of the current line */
    char c, last_c;    /* current character and last character */

    file_ptr = fopen("input.txt", "r");
    if (!file_ptr) {
        exit(EXIT_FAILURE);
        fprintf(stderr, "File could not be read!");
    }

    while ((c = fgetc(file_ptr)) != EOF) {
        if (c == '\n') {
            player_score += calculate_score(col_a, strategic_response(col_a, col_b));
            col_a = col_b = 0;
        } else if ((c >= 'A' && c <= 'C') || (c >= 'X' && c <= 'Z')) {
            if (last_c == ' ') {
                col_b = c;
            } else {
                col_a = c;
            }
        }

        if (c != '\r') {/* ignore CR (Windows files) */
            last_c = c;
        }
    }
    fclose(file_ptr);

    printf("Following the Elf's instructions for the second column, what \
would your total score be if everything goes exactly according to your \
strategy guide? %d\n", player_score);
}

int main(int argc, char **argv) {
    part_two();
    return 0;
}