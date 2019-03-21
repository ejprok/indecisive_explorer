#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "headers.h"

char player_turn = 'n';
int move_history_index = 1;
struct MoveInfo *move_history;



int main(int argc, char **argv) {
    //initial setup 
    move_history = malloc(1000 * sizeof move_history);
    move_history[0].start = 0;
    move_history[0].end = 0;
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
        // check_game_over();

    }
}

void human_move() {
    //get valid human moves
    struct MoveInfo *moves = gen_human_moves(get_board());

    printf("\nHere are the valid moves:\n");

    //display valid moves
    int i;
    int max = moves[0].start;
    char** move_string_list = malloc(100 * 4 * sizeof * move_string_list);
    for (i=1; i<max; i++) {
        char* move_string = malloc(4*sizeof move_string);
        char* move_string_1 = convert_index_to_str(moves[i].start);
        char* move_string_2 = convert_index_to_str(moves[i].end); 
        move_string[0] = move_string_1[0];
        move_string[1] = move_string_1[1];
        move_string[2] = move_string_2[0];
        move_string[3] = move_string_2[1];
        move_string_list[i] = move_string;
        printf("%c%c%c%c  ", move_string[0], move_string[1], move_string[2], move_string[3]);
        
    }


    //prompt for move
    char* user_move = get_user_move();
    while (!check_valid_input(user_move, move_string_list, max)) {
    
        user_move = get_user_move();
    }
    printf("Move is valid\n");
    int index = check_valid_input(user_move, move_string_list, max);
    struct MoveInfo move_selected = moves[index];
    printf("The index is: %d\n", index);

    //using input, make a move
    apply_move(move_selected);
    player_turn = 'c';
    debug_board(get_board().human_bishops);

}

void computer_move() {

    player_turn = 'h';
    struct MoveInfo comp_move = minimax();
    apply_move(comp_move);
    print_game_history();
    debug_board(get_board().human_bishops);

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
    // while (player_turn == 'n') {
    get_which_player();
    // }
}

void get_which_player() {
    char user_input[100];
    fflush(stdin);
    fgets(user_input,100,stdin);
    if (user_input[0] == 'y') {
        player_turn = 'h';
        printf("Ok, you will go first\n\n");
    } else if (user_input[0] == 'n') {
        player_turn = 'c';
        printf("Ok, the computer will go first\n\n");
    } else {
        printf("Please enter y or n\n");
        get_which_player();

    }
}

char* get_user_move() {
    printf("\n\nPlease enter a valid move...\n");
    char* user_input = malloc(100 * sizeof user_input);
    fflush(stdin);
    fgets(user_input, 100, stdin);

    return user_input;
    
}

int check_valid_input(char* input, char** move_string_list, int list_size) {
    if (!(input[0] == 'a' || input[0] == 'A' || input[0] == 'b' || input[0] == 'B' ||
        input[0] == 'c' || input[0] == 'C' || input[0] == 'd' || input[0] == 'D' ||
        input[0] == 'e' || input[0] == 'E' || input[0] == 'f' || input[0] == 'F' ||
        input[0] == 'g' || input[0] == 'G' || input[0] == 'h' || input[0] == 'H')) 
    {
        return 0;
    }
    if (!(input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4' ||
        input[1] == '5' || input[1] == '6' )) 
    {
        return 0;
    }
    if (!(input[2] == 'a' || input[2] == 'A' || input[2] == 'b' || input[2] == 'B' ||
        input[2] == 'c' || input[2] == 'C' || input[2] == 'd' || input[2] == 'D' ||
        input[2] == 'e' || input[2] == 'E' || input[2] == 'f' || input[2] == 'F' ||
        input[2] == 'g' || input[2] == 'G' || input[2] == 'h' || input[2] == 'H')) 
    {
        return 0;
    }
    if (!(input[3] == '1' || input[3] == '2' || input[3] == '3' || input[3] == '4' ||
        input[3] == '5' || input[3] == '6' )) 
    {
        return 0;
    }
    
    int move_location_start = convert_str_to_index(input);
    int move_location_end   = convert_str_to_index(&input[2]);
    int flag = 0;
    int i=1;
    for (i=1; i< list_size; i++) {
        int valid_move_start   = convert_str_to_index(move_string_list[i]);
        int valid_move_end = convert_str_to_index(&move_string_list[i][2]);
        if ((move_location_start == valid_move_start) && (move_location_end == valid_move_end))
        {
            flag = i;

        }
    }

    return flag;

}

void apply_move(struct MoveInfo move) {
    struct GameBoard gm_brd = get_board();
    Bitboard start_loc = 1;
    start_loc = start_loc << move.start;
    Bitboard end_loc = 1;
    end_loc = end_loc << move.end;

    //move the piece
    switch (move.piece_type)
    {
        case 1:
            //human king
            gm_brd.human_kings &= ~start_loc;
            gm_brd.human_kings |= end_loc;
            break;
        case 2:
            //human bishop
            gm_brd.human_bishops &= ~start_loc;
            if((move.end % 8) >=4 ) {
                gm_brd.human_bishops |= end_loc;
            } else {
                gm_brd.human_horses |= end_loc;
            }
            break;
        case 3:
            //human horse
            gm_brd.human_horses &= ~start_loc;
            if((move.end % 8) >=4 ) {
                gm_brd.human_bishops |= end_loc;
            } else {
                gm_brd.human_horses |= end_loc;
            } 
            break;
        case 4:
            //human pawn
            gm_brd.human_pawns &= ~start_loc;
            gm_brd.human_pawns |= end_loc;
            break;
        case 5:
            //comp king
            gm_brd.comp_kings &= ~start_loc;
            gm_brd.comp_kings |= end_loc;
            break;
        case 6:
            //comp bishop
            gm_brd.comp_bishops &= ~start_loc;
            if((move.end % 8) >=4 ) {
                gm_brd.comp_bishops |= end_loc;
            } else {
                gm_brd.comp_horses |= end_loc;
            }
            break;
        case 7:
            //comp horse
            gm_brd.comp_horses &= ~start_loc;
            if((move.end % 8) >=4 ) {
                gm_brd.comp_bishops |= end_loc;
            } else {
                gm_brd.comp_horses |= end_loc;
            } 
            break;
        case 8:
            //comp pawn
            gm_brd.comp_pawns &= ~start_loc;
            gm_brd.comp_pawns |= end_loc;
            break;

    
        default:
            break;
    }

    //remove captured piece
    switch (move.piece_cap)
    {
        case 1:
            //human king
            gm_brd.human_kings &= ~end_loc;
            break;
        case 2:
            //human bishop
            gm_brd.human_bishops &= ~end_loc;
            break;
        case 3:
            //human horse
            gm_brd.human_horses &= ~end_loc;
            break;
        case 4:
            //human pawn
            gm_brd.human_pawns &= ~end_loc;
            break;
        case 5:
            //comp king
            gm_brd.comp_kings &= ~end_loc;
            break;
        case 6:
            //comp bishop
            gm_brd.comp_bishops &= ~end_loc;
            break;
        case 7:
            //comp horse
            gm_brd.comp_horses &= ~end_loc;
            break;
        case 8:
            //comp pawn
            gm_brd.comp_pawns &= ~end_loc;
            break;

    
        default:
            break;
    }

    //add end bit to the board
    move_history[move_history_index] = move;
    move_history_index++;
    

    update_board(gm_brd);
    update_extra_boards();
}

void undo_move() {
    struct GameBoard gm_brd = get_board();
    struct MoveInfo move = move_history[move_history_index-1];

    Bitboard start_loc = 1;
    start_loc = start_loc << move.start;
    Bitboard end_loc = 1;
    end_loc = end_loc << move.end;

    //move the piece
    switch (move.piece_type)
    {
        case 1:
            //human king
            gm_brd.human_kings &= ~end_loc;
            gm_brd.human_kings |= start_loc;
            break;
        case 2:
            //human bishop
            if((move.start % 8) >=4 ) {
                gm_brd.human_bishops |= start_loc;
            } else {
                gm_brd.human_horses |= start_loc;
            }
            if((move.end % 8) >=4 ) {
                gm_brd.human_bishops &= ~end_loc;
            } else {
                gm_brd.human_horses &= ~end_loc;
            }
            break;
        case 3:
            //human horse
            if((move.start % 8) >= 4 ) {
                gm_brd.human_bishops |= start_loc;
            } else {
                gm_brd.human_horses |= start_loc;
            } 
            if((move.end % 8) >=4 ) {
                gm_brd.human_bishops &= ~end_loc;
            } else {
                gm_brd.human_horses &= ~end_loc;
            }
            break;
        case 4:
            //human pawn
            gm_brd.human_pawns &= ~end_loc;
            gm_brd.human_pawns |= start_loc;
            break;
        case 5:
            //comp king
            gm_brd.comp_kings &= ~end_loc;
            gm_brd.comp_kings |= start_loc;
            break;
        case 6:
            //comp bishop
            if((move.start % 8) >=4 ) {
                gm_brd.comp_bishops |= start_loc;
            } else {
                gm_brd.comp_horses |= start_loc;
            }
            if((move.end % 8) >=4 ) {
                gm_brd.comp_bishops &= ~end_loc;
            } else {
                gm_brd.comp_horses &= ~end_loc;
            }
            break;
        case 7:
            //comp horse
            if((move.start % 8) >=4 ) {
                gm_brd.comp_bishops |= start_loc;
            } else {
                gm_brd.comp_horses |= start_loc;
            }
            if((move.end % 8) >=4 ) {
                gm_brd.comp_bishops &= ~end_loc;
            } else {
                gm_brd.comp_horses &= ~end_loc;
            }
            break;
        case 8:
            //comp pawn
            gm_brd.comp_pawns &= ~end_loc;
            gm_brd.comp_pawns |= start_loc;
            break;

    
        default:
            break;
    }

    //remove captured piece
    switch (move.piece_cap)
    {
        case 1:
            //human king
            gm_brd.human_kings |= end_loc;
            break;
        case 2:
            //human bishop
            gm_brd.human_bishops |= end_loc;
            break;
        case 3:
            //human horse
            gm_brd.human_horses |= end_loc;
            break;
        case 4:
            //human pawn
            gm_brd.human_pawns |= end_loc;
            break;
        case 5:
            //comp king
            gm_brd.comp_kings |= end_loc;
            break;
        case 6:
            //comp bishop
            gm_brd.comp_bishops |= end_loc;
            break;
        case 7:
            //comp horse
            gm_brd.comp_horses |= end_loc;
            break;
        case 8:
            //comp pawn
            gm_brd.comp_pawns |= end_loc;
            break;

    
        default:
            break;
    }

    //add end bit to the board
    move_history_index--;
    

    update_board(gm_brd);
    update_extra_boards();
}

void print_game_history() {
    int i;
    printf("Move History ----------------------------\n");
    for (i=1; i<move_history_index; i++) {
        printf("Piece: %d\tStart: %d\tEnd: %d\t\tPiece Cap: %d\n", move_history[i].piece_type, move_history[i].start, move_history[i].end, move_history[i].piece_cap);
    }
    printf("End Move History ------------------------\n");
}
void check_game_over() {
    exit(1);
}


