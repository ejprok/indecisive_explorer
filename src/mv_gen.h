#ifndef _MV_GEN_
#define _MV_GEN_
#include "brd.h"
typedef uint64_t Bitboard;
struct MoveInfo
{
    Bitboard move;
    int start;
    int end;
    int piece_cap;
    
};

struct MoveInfo* gen_human_moves();
void gen_computer_moves();

int* loop_thru_brd(Bitboard bit_brd, int start_bit, int end_bit);
Bitboard* get_piece_locations(Bitboard bit_brd);

Bitboard get_king_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd);
Bitboard get_bishop_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd);
Bitboard get_horse_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd);
Bitboard get_pawn_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd);

void print_bits(Bitboard data);

int check_attack(Bitboard location, struct GameBoard gm_brd, int piece_type);

Bitboard prepare_move_header(Bitboard move, Bitboard location, Bitboard piece);
struct MoveInfo prepare_move(Bitboard move, int start, int end, int piece_cap);

int get_moves_for_type(struct GameBoard gm_brd, struct MoveInfo *move_list, int move_list_size, int piece_type);

void print_header(Bitboard data);

void add_move(Bitboard single_move, struct MoveInfo *move_list, int move_list_size );
void print_moves(struct MoveInfo *moves, int size );





#endif
