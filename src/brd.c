#include "brd.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//rank 1
const int A1 = 0;
const int B1 = 1;
const int C1 = 2;
const int D1 = 3;
const int E1 = 4;
const int F1 = 5;
const int G1 = 6;
const int H1 = 7;

//rank 2
const int A2 = 8;
const int B2 = 9;
const int C2 = 10;
const int D2 = 11;
const int E2 = 12;
const int F2 = 13;
const int G2 = 14;
const int H2 = 15;

//rank 3
const int A3 = 16;
const int B3 = 17;
const int C3 = 18;
const int D3 = 19;
const int E3 = 20;
const int F3 = 21;
const int G3 = 22;
const int H3 = 23;

//rank 4
const int A4 = 24;
const int B4 = 25;
const int C4 = 26;
const int D4 = 27;
const int E4 = 28;
const int F4 = 29;
const int G4 = 30;
const int H4 = 31;

//rank 5
const int A5 = 32;
const int B5 = 33;
const int C5 = 34;
const int D5 = 35;
const int E5 = 36;
const int F5 = 37;
const int G5 = 38;
const int H5 = 39;

//rank 6
const int A6 = 40;
const int B6 = 41;
const int C6 = 42;
const int D6 = 43;
const int E6 = 44;
const int F6 = 45;
const int G6 = 46;
const int H6 = 47;

typedef uint64_t Bitboard;

const Bitboard valid_mask = 0b0000000000000000111111111111111111111111111111111111111111111111;
const Bitboard clearAFile = 0b011111110111111101111111011111110111111101111111;
const Bitboard clearBFile = 0b101111111011111110111111101111111011111110111111;
const Bitboard clearCFile = 0b110111111101111111011111110111111101111111011111;
const Bitboard clearDFile = 0b111011111110111111101111111011111110111111101111;
const Bitboard clearEFile = 0b111101111111011111110111111101111111011111110111;
const Bitboard clearFFile = 0b111110111111101111111011111110111111101111111011;
const Bitboard clearGFile = 0b111111011111110111111101111111011111110111111101;
const Bitboard clearHFile = 0b111111101111111011111110111111101111111011111110;

Bitboard bish_mask[64];


struct GameBoard game_board;

void init_masks() {


    //for bishop
    int i;
    for(i=0; i<48; i++) {
        bish_mask[i] = 0;
    }
    // 4-7
    bish_mask[4] = 0b000000000001010000100010010000011000000000000000;
    bish_mask[5] = 0b000000000000101000010001001000000100000010000000;
    bish_mask[6] = 0b000000000000010100001000000100000010000001000000;
    bish_mask[7] = 0b000000000000001000000100000010000001000000100000;

    // 12-15
    bish_mask[12] = 0b000101000000000000010100001000100100000110000000;
    bish_mask[13] = 0b000010100000000000001010000100010010000001000000;
    bish_mask[14] = 0b000001010000000000000101000010000001000000100000;
    bish_mask[15] = 0b000000100000000000000010000001000000100000010000;

    // 20-23
    bish_mask[20] = 0b001000100001010000000000000101000010001001000001;
    bish_mask[21] = 0b000100010000101000000000000010100001000100100000;
    bish_mask[22] = 0b000010000000010100000000000001010000100000010000;
    bish_mask[23] = 0b000001000000001000000000000000100000010000001000;

    // 28-31
    bish_mask[28] = 0b010000010010001000010100000000000001010000100010;
    bish_mask[29] = 0b001000000001000100001010000000000000101000010001;
    bish_mask[30] = 0b000100000000100000000101000000000000010100001000;
    bish_mask[31] = 0b000010000000010000000010000000000000001000000100;

    // 36-39
    bish_mask[36] = 0b100000000100000100100010000101000000000000010100;
    bish_mask[37] = 0b010000000010000000010001000010100000000000001010;
    bish_mask[38] = 0b001000000001000000001000000001010000000000000101;
    bish_mask[39] = 0b000100000000100000000100000000100000000000000010;

    //44-47
    bish_mask[44] = 0b000000001000000001000001001000100001010000000000;
    bish_mask[45] = 0b100000000100000000100000000100010000101000000000;
    bish_mask[46] = 0b010000000010000000010000000010000000010100000000;
    bish_mask[47] = 0b001000000001000000001000000001000000001000000000;

    for(i=0; i<48; i++) {
        if (bish_mask[i]) {
            // bish_mask[i] = swap_uint64(bish_mask[i]);
            debug_board(bish_mask[i]);
        }
    }
}

void init_board() {
    game_board.human_kings      = 0b0000000000000000000110000000000000000000000000000000000000000000;
    game_board.human_bishops    = 0b0000000000000000110000000000000000000000000000000000000000000000;
    game_board.human_horses     = 0b0000000000000000000000110000000000000000000000000000000000000000;
    game_board.human_pawns      = 0b0000000000000000000000000111111000000000000000000000000000000000;

    game_board.comp_kings     = 0b0000000000000000000000000000000000000000000000000000000000011000;
    game_board.comp_bishops   = 0b0000000000000000000000000000000000000000000000000000000011000000;
    game_board.comp_horses    = 0b0000000000000000000000000000000000000000000000000000000000000011;
    game_board.comp_pawns     = 0b0000000000000000000000000000000000000000000000000111111000000000;
    
    update_extra_boards();
}

struct GameBoard get_board() {
    return game_board;
}

void update_extra_boards() {
    game_board.comp_pieces = game_board.comp_kings | game_board.comp_bishops | game_board.comp_horses | game_board.comp_pawns;
    game_board.human_pieces = game_board.human_kings | game_board.human_bishops | game_board.human_horses | game_board.human_pawns;
    game_board.all_pieces = game_board.comp_pieces | game_board.human_pieces;
}



void print_board() {
    //print 1st rank
    int i = 1;
    struct GameBoard board_copy = game_board;

    printf("\t   ------------------------" ANSI_COLOR_RED " Computer\n\t"  ANSI_COLOR_RESET);
    printf(" 6 ");
    while (i <= 48) {

        if (board_copy.comp_kings & 0b01) {
            printf(ANSI_COLOR_RED " K " ANSI_COLOR_RESET);
        } else if (board_copy.comp_bishops & 0b01) {
            printf(ANSI_COLOR_RED " B " ANSI_COLOR_RESET);
        } else if (board_copy.comp_horses & 0b01) {
            printf(ANSI_COLOR_RED " H " ANSI_COLOR_RESET);
        } else if (board_copy.comp_pawns & 0b01) {
            printf(ANSI_COLOR_RED " P " ANSI_COLOR_RESET);
        } else if (board_copy.human_kings & 0b01) {
            printf(ANSI_COLOR_BLUE " k " ANSI_COLOR_RESET);
        } else if (board_copy.human_bishops & 0b01) {
            printf(ANSI_COLOR_BLUE " b " ANSI_COLOR_RESET);
        } else if (board_copy.human_horses & 0b01) {
            printf(ANSI_COLOR_BLUE " h " ANSI_COLOR_RESET);
        } else if (board_copy.human_pawns & 0b01) {
            printf(ANSI_COLOR_BLUE " p " ANSI_COLOR_RESET);
        }
        else {
            printf(ANSI_COLOR_GREEN " - " ANSI_COLOR_RESET);
        }
        if ((i % 8 == 0) && (i != 48)) {
            printf("\n\t");
            int rank = (48 - i) / 8 ;
            printf(" %d ", rank);
        }
        board_copy.comp_kings    = board_copy.comp_kings >> 1;
        board_copy.comp_bishops  = board_copy.comp_bishops >> 1;
        board_copy.comp_horses   = board_copy.comp_horses >> 1;
        board_copy.comp_pawns    = board_copy.comp_pawns >> 1;
        board_copy.human_kings    = board_copy.human_kings >> 1;
        board_copy.human_bishops  = board_copy.human_bishops >> 1;
        board_copy.human_horses   = board_copy.human_horses >> 1;
        board_copy.human_pawns    = board_copy.human_pawns >> 1;
        i++;

    }
    printf("\n\t   ------------------------" ANSI_COLOR_BLUE " Human\n" ANSI_COLOR_RESET);
    printf("\t    A  B  C  D  E  F  G  H \n");

}

void debug_board(Bitboard brd) {
    printf("\n");
    int i = 1;
    while (i <= 48) {
        int output = brd & 0b01;
        printf(" %d ", output);
        if (i % 8 == 0) {
            printf("\n");
        }
        
        i++;
    } 
    printf("\n");
}

uint64_t swap_uint64( uint64_t val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    val = (val << 32) | (val >> 32);
    return val;
}
