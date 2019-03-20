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
const Bitboard clearHFile = 0b011111110111111101111111011111110111111101111111;
const Bitboard clearGFile = 0b101111111011111110111111101111111011111110111111;
const Bitboard clearFFile = 0b110111111101111111011111110111111101111111011111;
const Bitboard clearEFile = 0b111011111110111111101111111011111110111111101111;
const Bitboard clearDFile = 0b111101111111011111110111111101111111011111110111;
const Bitboard clearCFile = 0b111110111111101111111011111110111111101111111011;
const Bitboard clearBFile = 0b111111011111110111111101111111011111110111111101;
const Bitboard clearAFile = 0b111111101111111011111110111111101111111011111110;

Bitboard cl_r_a, cl_l_a, cl_r_b, cl_l_b, cl_r_c, cl_l_c, cl_r_d, cl_l_d, cl_r_e, cl_l_e, cl_r_f, cl_l_f, cl_r_g, cl_l_g, cl_r_h, cl_l_h;

Bitboard bish_mask[64];


struct GameBoard game_board;

void init_masks() {


    //for bishop
    int i;
    for(i=0; i<48; i++) {
        bish_mask[i] = 0;
    }


   // 4-7
    bish_mask[44] = 0b000000000010100001000100100000100000000100000000;

    bish_mask[45] = 0b000000000101000010001000000001000000001000000001;
    bish_mask[46] = 0b000000001010000000010000000010000000010000000010;
    bish_mask[47] = 0b000000000100000000100000000100000000100000000100;

    // 12-15
    bish_mask[36] = 0b001010000000000000101000010001001000001000000001;
    bish_mask[37] = 0b010100000000000001010000100010000000010000000010;
    bish_mask[38] = 0b101000000000000010100000000100000000100000000100;
    bish_mask[39] = 0b010000000000000001000000001000000001000000001000;

    // 20-23
    bish_mask[28] = 0b010001000010100000000000001010000100010010000010;
    bish_mask[29] = 0b100010000101000000000000010100001000100000000100;
    bish_mask[30] = 0b000100001010000000000000101000000001000000001000;
    bish_mask[31] = 0b001000000100000000000000010000000010000000010000;

    // 28-31
    bish_mask[20] = 0b100000100100010000101000000000000010100001000100;
    bish_mask[21] = 0b000001001000100001010000000000000101000010001000;
    bish_mask[22] = 0b000010000001000010100000000000001010000000010000;
    bish_mask[23] = 0b000100000010000001000000000000000100000000100000;

    // 36-39
    bish_mask[12] = 0b000000011000001001000100001010000000000000101000;
    bish_mask[13] = 0b000000100000010010001000010100000000000001010000;
    bish_mask[14] = 0b000001000000100000010000101000000000000010100000;
    bish_mask[15] = 0b000010000001000000100000010000000000000001000000;

    //44-47
    bish_mask[4] = 0b000000000000000110000010010001000010100000000000;

    bish_mask[5] = 0b000000010000001000000100100010000101000000000000;
    bish_mask[6] = 0b000000100000010000001000000100001010000000000000;
    bish_mask[7] = 0b000001000000100000010000001000000100000000000000;


    //clear files
    cl_r_a = clearBFile & clearCFile & clearDFile & clearEFile & clearFFile & clearGFile & clearHFile;
    cl_r_b = clearCFile & clearDFile & clearEFile & clearFFile & clearGFile & clearHFile;
    cl_r_c = clearDFile & clearEFile & clearFFile & clearGFile & clearHFile;
    cl_r_d = clearEFile & clearFFile & clearGFile & clearHFile;
    cl_r_e = clearFFile & clearGFile & clearHFile;
    cl_r_f = clearGFile & clearHFile;
    cl_r_g = clearHFile;

    cl_l_h = clearAFile & clearBFile & clearCFile & clearDFile & clearEFile & clearFFile & clearGFile;
    cl_l_g = clearAFile & clearBFile & clearCFile & clearDFile & clearEFile & clearFFile;
    cl_l_f = clearAFile & clearBFile & clearCFile & clearDFile & clearEFile;
    cl_l_e = clearAFile & clearBFile & clearCFile & clearDFile;
    cl_l_d = clearAFile & clearBFile & clearCFile;
    cl_l_c = clearAFile & clearBFile;
    cl_l_b = clearAFile;

}

void init_board() {
    game_board.human_kings      = 0b0000000000000000000110000000000000000000000000000000000000000000;
    game_board.human_bishops    = 0b0000000000000000110000000000000000000000000000000000000000000000;
    game_board.human_horses     = 0b0000000000000000000000110000000000000000000000000000000000000000;
    game_board.human_pawns      = 0b0000000000000000000000000111111000000000000000000000000000000000;

    game_board.comp_kings       = 0b0000000000000000000000000000000000000000000000000000000000011000;
    game_board.comp_bishops     = 0b0000000000000000000000000000000000000000000000000000000011000000;
    game_board.comp_horses      = 0b0000000000000000000000000000000000000000000000000000000000000011;
    game_board.comp_pawns       = 0b0000000000000000000000000000000000000000000000000111111000000000;
    
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
        brd = brd >> 1;
    } 
    printf("\n");
}

uint64_t swap_uint64( uint64_t val )
{
    val = val << 8;
    val = (val & 0x00000000FFFFFFFF) << 32 | (val & 0xFFFFFFFF00000000) >> 32;
    val = (val & 0x0000FFFF0000FFFF) << 16 | (val & 0xFFFF0000FFFF0000) >> 16;
    val = (val & 0x00FF00FF00FF00FF) << 8  | (val & 0xFF00FF00FF00FF00) >> 8;
    val = (val & 0x0F0F0F0F0F0F0F0F) << 4  | (val & 0xF0F0F0F0F0F0F0F0) >> 4;
    val = (val & 0x3333333333333333) << 2  | (val & 0xCCCCCCCCCCCCCCCC) >> 2;
    val = (val & 0x5555555555555555) << 1  | (val & 0xAAAAAAAAAAAAAAAA) >> 1;
    return val >> 8 ;
}
