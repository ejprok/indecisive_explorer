#include <stdlib.h>
#include <stdio.h>
#include "mv_gen.h"
#include "brd.h"

//add a move to an array of valid moves
void add_move(int location, Bitboard valid_moves, struct MoveInfo** move_list) {
    struct MoveInfo* copy_list = *move_list;
    int index = copy_list[0].location;
    copy_list = realloc(copy_list, (index + 1) * sizeof *copy_list);
    copy_list[index].location = location;
    copy_list[index].moves = valid_moves;
    copy_list[0].location = index + 1;
    printf("Location is: %d\n", copy_list[index].location);
    printf("The moves are:\n");
    debug_board(valid_moves);
}

void gen_human_moves(struct GameBoard gm_brd ) {
    struct MoveInfo *move_list = malloc(100 * sizeof *move_list);

    //first element is for keeping track of array size
    struct MoveInfo data;
    data.location = 1;
    move_list[0] = data;

    //check the kings
    int* kings = loop_thru_brd(gm_brd.human_kings, 0, 7);
    int i;
    int max = kings[0];
    if (max > 0) {
        for (i=1; i<=max; i++) {
            Bitboard temp_board = get_king_moves(kings[i], gm_brd.human_pieces);
            if (temp_board != 0) {
                // add_move(kings[i], temp_board, &move_list);
            }
        }
    }

    free(kings);
    //check the bishops

    //check the horses

    //check the pawns

    free(move_list);
}

void gen_computer_moves() {

}


Bitboard get_king_moves(int location, Bitboard invalid_locations) {
    Bitboard loc = 0b01 << location;
    Bitboard move;

    //check if the king is at edge of board
    if (location == 47 || location == 39 || location == 7 || location == 0) {
        return 0;
    }

    //if leftwing king
    if ((location <= 3 ) || (location <= 43 && location > 4)) {
        move = loc >> 1;
    }
    //if rightwing king 
    if ((location >= 4 && location < 43) || (location >= 44)){
        move = loc << 1;
    }
    
    move = move & ~invalid_locations;
    return move;

}

//returns a pointer to a list of the indexes of pieces in a board
int* loop_thru_brd(Bitboard bit_brd, int start_bit, int end_bit) {
    int i;
    int *list = malloc(10 * sizeof *list);
    //to say that the length is 0
    list[0] = 0;
    int count = 1;
    for (i = start_bit; i <= end_bit; i++ ) {
        if (bit_brd & 0b01) { 
            list[count] = i;
            list[0] = count;
            count++;

        }
        bit_brd = bit_brd >> 1;
    }
    return list;
}