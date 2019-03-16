#ifndef _BRD_
#define _BRD_

#include <stdint.h>

extern const int A1;
//rank 1
extern const int A1;
extern const int B1;
extern const int C1;
extern const int D1;
extern const int E1;
extern const int F1;
extern const int G1;
extern const int H1;

//rank 2
extern const int A2;
extern const int B2;
extern const int C2;
extern const int D2;
extern const int E2;
extern const int F2;
extern const int G2;
extern const int H2;

//rank 3
extern const int A3;
extern const int B3;
extern const int C3;
extern const int D3;
extern const int E3;
extern const int F3;
extern const int G3;
extern const int H3;

//rank 4
extern const int A4;
extern const int B4;
extern const int C4;
extern const int D4;
extern const int E4;
extern const int F4;
extern const int G4;
extern const int H4;

//rank 5
extern const int A5;
extern const int B5;
extern const int C5;
extern const int D5;
extern const int E5;
extern const int F5;
extern const int G5;
extern const int H5;

//rank 6
extern const int A6;
extern const int B6;
extern const int C6;
extern const int D6;
extern const int E6;
extern const int F6;
extern const int G6;
extern const int H6;

typedef uint64_t Bitboard;
struct GameBoard
{
    //computer pieces
    Bitboard comp_kings;
    Bitboard comp_bishops;
    Bitboard comp_horses;
    Bitboard comp_pawns;
    //human pieces
    Bitboard human_kings;
    Bitboard human_bishops;
    Bitboard human_horses;
    Bitboard human_pawns;

    //combined pieces
    Bitboard all_pieces;
    Bitboard comp_pieces;
    Bitboard human_pieces;
};



void print_board();
void init_board();
void update_extra_boards();
struct GameBoard get_board();
void debug_board(Bitboard brd);

#endif