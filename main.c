#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "headers.h"

char player_turn = 'n';
void get_which_player();
void ask_which_player();
void game_loop();
void check_game_over();
void human_move();
void computer_move();
char* convert_index_to_str(int input);
int get_user_move();

int main(int argc, char **argv) {
    //initial setup 
    init_board();
    init_masks();

    //get the first player
    ask_which_player();


    //run the game loop
    game_loop();
    //print out who wins/loses
}

void game_loop() {
    while(1) {

        print_board();
        if (player_turn == 'h') {
            human_move();
        } else if (player_turn == 'c') {
            computer_move();
        }
        check_game_over();

    }
}

void human_move() {
    //get valid human moves
    struct MoveInfo *moves = gen_human_moves(get_board());

    printf("\nHere are the valid moves:\n");

    //display valid moves
    int i;
    int max = moves[0].start;
    for (i=1; i<max; i++) {
        char* start = convert_index_to_str(moves[i].start);
        char* end   = convert_index_to_str(moves[i].end);
        printf("%c%c%c%c  ", start[0], start[1], end[0], end[1]);
        
    }
    printf("\n\nPlease enter a valid move...\n");

    //prompt for move

    //using input, make a move

    //if wrong, re-prompt

}

void computer_move() {

}

//take a string as input and convert to an index
int convert_str_to_index(char *input) {
    int location, row, col;
    switch (input[0])
    {
        case 'A':
            col = 0;
            break;
        case 'a':
            col = 0;
            break;

        case 'B':
            col = 1;
            break;
        case 'b':
            col = 1;
            break;

        case 'C':
            col = 2;
            break;
        case 'c':
            col = 2;
            break;

        case 'D':
            col = 3;
            break;
        case 'd':
            col = 3;
            break;

        case 'E':
            col = 4;
            break;
        case 'e':
            col = 4;
            break;

        case 'F':
            col = 5;
            break;
        case 'f':
            col = 5;
            break;

        case 'G':
            col = 6;
            break;
        case 'g':
            col = 6;
            break;

        case 'H':
            col = 7;
            break;
        case 'h':
            col = 7;
            break;



        default:

            break;
    }
    switch (input[1])
    {
        case '6':
            row = 0;
            break;
        case '5':
            row = 1;
            break;
        case '4':
            row = 2;
            break;
        case '3':
            row = 3;
            break;
        case '2':
            row = 4;
            break;
        case '1':
            row = 5;
            break;

        default:
            break;
    }
    location = (row * 8) + col;
    return location;
}

//take an int as input and convert to a str output
char* convert_index_to_str(int input) {
    char *loc_str = malloc(2 * sizeof *loc_str);
    int col = input % 8;
    int row = input / 8;
    switch (col)
    {
        case 0:
            loc_str[0] = 'A';
            break;

        case 1:
            loc_str[0] = 'B';
            break;
        case 2:
            loc_str[0] = 'C';
            break;
        case 3:
            loc_str[0] = 'D';
            break;
        case 4:
            loc_str[0] = 'E';
            break;
        case 5:
            loc_str[0] = 'F';
            break;
        case 6:
            loc_str[0] = 'G';
            break;
        case 7:
            loc_str[0] = 'H';
            break;
        default:
            break;
    }
    switch (row)
    {
        case 0:
            loc_str[1] = '6';
            break;

        case 1:
            loc_str[1] = '5';
            break;
        case 2:
            loc_str[1] = '4';
            break;
        case 3:
            loc_str[1] = '3';
            break;
        case 4:
            loc_str[1] = '2';
            break;
        case 5:
            loc_str[1] = '1';
            break;
        default:
            break;
    }
    return loc_str;
}

void ask_which_player() {
    printf("Would you like to go first? (enter y or n)\n");
    while (player_turn == 'n') {
        get_which_player();
    }
}

void get_which_player() {
    char user_input[100];
    fflush(stdin);
    fgets(user_input,2,stdin);
    if (user_input[0] == 'y') {
        player_turn = 'h';
        printf("Ok, you will go first\n\n");
    } else if (user_input[0] == 'n') {
        player_turn = 'c';
        printf("Ok, the computer will go first\n\n");
    } else {
        printf("Please enter y or n\n");

    }
}

int get_user_move() {
    char user_input[4];
    fflush(stdin);
    fgets(user_input, 5, stdin);
    
}

void check_game_over() {
    exit(1);
}


