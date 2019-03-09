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

int main(int argc, char **argv) {
    //get the first player
    ask_which_player();
    //run the game loop
    print_board();
    // game_loop();
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

}

void computer_move() {

}

void ask_which_player() {
    printf("Would you like to go first? (enter y or n)\n");
    while (player_turn == 'n') {
        get_which_player();
    }
}

void get_which_player() {
    char user_input[1];
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

void check_game_over() {

}


