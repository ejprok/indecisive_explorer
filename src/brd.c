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


struct GameBoard game_board;

void init_board() {
    game_board.comp_kings   = 0b0000000000000000000110000000000000000000000000000000000000000000;
    game_board.comp_bishops  = 0b0000000000000000110000000000000000000000000000000000000000000000;
    game_board.comp_horses   = 0b0000000000000000000000110000000000000000000000000000000000000000;
    game_board.comp_pawns    = 0b0000000000000000000000000111111000000000000000000000000000000000;

    game_board.human_kings   = 0b0000000000000000000000000000000000000000000000000000000000011000;
    game_board.human_bishops = 0b0000000000000000000000000000000000000000000000000000000011000000;
    game_board.human_horses  = 0b0000000000000000000000000000000000000000000000000000000000000011;
    game_board.human_pawns   = 0b0000000000000000000000000000000000000000000000000111111000000000;
}

void print_board() {
    //print 1st rank
    int i = 1;
    struct GameBoard board_copy = game_board;

    printf("\t   ------------------------" ANSI_COLOR_RED " Computer\n\t"  ANSI_COLOR_RESET);
    printf(" 6 ");
    while (i <= 48) {

        if (board_copy.comp_kings & 0b01) {
            printf(ANSI_COLOR_BLUE " K " ANSI_COLOR_RESET);
        } else if (board_copy.comp_bishops & 0b01) {
            printf(ANSI_COLOR_BLUE " B " ANSI_COLOR_RESET);
        } else if (board_copy.comp_horses & 0b01) {
            printf(ANSI_COLOR_BLUE " H " ANSI_COLOR_RESET);
        } else if (board_copy.comp_pawns & 0b01) {
            printf(ANSI_COLOR_BLUE " P " ANSI_COLOR_RESET);
        } else if (board_copy.human_kings & 0b01) {
            printf(ANSI_COLOR_RED " k " ANSI_COLOR_RESET);
        } else if (board_copy.human_bishops & 0b01) {
            printf(ANSI_COLOR_RED " b " ANSI_COLOR_RESET);
        } else if (board_copy.human_horses & 0b01) {
            printf(ANSI_COLOR_RED " h " ANSI_COLOR_RESET);
        } else if (board_copy.human_pawns & 0b01) {
            printf(ANSI_COLOR_RED " p " ANSI_COLOR_RESET);
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

