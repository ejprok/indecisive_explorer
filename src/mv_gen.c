#include <stdlib.h>
#include <stdio.h>
#include "mv_gen.h"
#include "brd.h"

void gen_human_moves(struct GameBoard gm_brd ) {
    //check the kings
    int* kings = loop_thru_brd(gm_brd.human_kings, 0, 7);
    int i;
    if (kings[0] > 0) {
        for (i=1; i<kings[0]; i++) {
            printf("Here is a king %d\n", kings[i]);
        }
    }

    free(kings);
    //check the bishops

    //check the horses

    //check the pawns

}

void gen_computer_moves() {

}

//returns a pointer to a list of the indexes of pieces in a board
int* loop_thru_brd(Bitboard bit_brd, int start_bit, int end_bit) {
    int i;
    int *list = malloc(2 * sizeof *list);
    //to say that the length is 0
    list[0] = 0;
    int count = 1;
    for (i = start_bit; i <= end_bit; i++ ) {
        if (bit_brd & 0b01) { 
            list[count] = i;
            list[0] = count;
            count++;
            list = realloc(list, count * sizeof *list);
        }
        bit_brd = bit_brd >> 1;
    }
    return list;
}