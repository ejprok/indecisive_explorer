#ifndef _MV_GEN_
#define _MV_GEN_

typedef uint64_t Bitboard;

void gen_human_moves();
void gen_computer_moves();
int* loop_thru_brd(Bitboard bit_brd, int start_bit, int end_bit);
Bitboard get_king_moves(int location, Bitboard invalid_locations);

struct MoveInfo
{
    Bitboard moves;
    int location;
    
};


#endif
