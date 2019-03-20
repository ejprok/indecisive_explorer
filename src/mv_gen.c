#include <stdlib.h>
#include <stdio.h>
#include "mv_gen.h"



struct MoveInfo* gen_human_moves(struct GameBoard gm_brd ) {
    //inialize the array of moves
    struct MoveInfo *move_list = malloc(1000 * sizeof *move_list);
    int move_list_size = 0;

     //////////////////////////////////////////////////////////////
    //KINGS
    move_list_size = get_moves_for_type(gm_brd, move_list, move_list_size, 1);

     //////////////////////////////////////////////////////////////
    //BISHOPS
    move_list_size = get_moves_for_type(gm_brd, move_list, move_list_size, 2);

    //check the horses
    move_list_size = get_moves_for_type(gm_brd, move_list, move_list_size, 3);

    //check the pawns
    move_list_size = get_moves_for_type(gm_brd, move_list, move_list_size, 4);

    print_moves(move_list, move_list_size);

    return move_list;

}

/*gets the moves for a type of piece and addes them to the movelist
    piece_type:
        1-4 human
        5-8 comp

*/
int get_moves_for_type(struct GameBoard gm_brd, struct MoveInfo *move_list, int move_list_size, int piece_type) {
    //get the locations for all the pieces
    Bitboard pieces;
    switch(piece_type) {
        case 1:
            pieces = gm_brd.human_kings;
            break;
        case 2:
            pieces = gm_brd.human_bishops;
            break;
        case 3:
            pieces = gm_brd.human_horses;
            break;
        case 4:
            pieces = gm_brd.human_pawns;
            break;
        case 5:
            pieces = gm_brd.comp_kings;
            break;
        case 6:
            pieces = gm_brd.comp_bishops;
            break;
        case 7:
            pieces = gm_brd.comp_horses;
            break;
        case 8:
            pieces = gm_brd.comp_pawns;
            break;
    }
    Bitboard* piece_locations = get_piece_locations(pieces);

    //generate moves for each piece
    int i;
    int max = piece_locations[0];

    //for each piece, add all possible moves to the list
    for(i=1; i<=max; i++) {
        Bitboard moves;
        switch(piece_type) {
            case 1:
                moves = get_king_moves(piece_locations[i], gm_brd.human_pieces, gm_brd);
                break;
            case 2:
                moves = get_bishop_moves(piece_locations[i], gm_brd.human_pieces, gm_brd);
                break;
            case 3:
                moves = get_horse_moves(piece_locations[i], gm_brd.human_pieces, gm_brd);
                break;
            case 4:
                moves = get_pawn_moves(piece_locations[i], gm_brd.human_pieces, gm_brd);
                break;
            case 5:
                moves = get_king_moves(piece_locations[i], gm_brd.comp_pieces, gm_brd);
                break;
            case 6:
                moves = get_bishop_moves(piece_locations[i], gm_brd.comp_pieces, gm_brd);
                break;
            case 7:
                moves = get_horse_moves(piece_locations[i], gm_brd.comp_pieces, gm_brd);
                break;
            case 8:
                moves = get_pawn_moves(piece_locations[i], gm_brd.comp_pieces, gm_brd);
                break;
        }
            
        
        //loop through each possible move and prepare it and add to list
        while(moves) {
            int move_location = __builtin_ctzll(moves);
            moves = moves >> (move_location + 1);
            moves = moves << (move_location + 1);
            Bitboard single_move = 1;
            single_move = single_move << move_location;
            int piece_cap = check_attack(single_move, gm_brd, piece_type);
            //prepare the move's header
            move_list[move_list_size] = prepare_move(single_move, piece_locations[i], move_location, piece_cap, piece_type);
            //add the move to the list of moves
            add_move(single_move, move_list, move_list_size);
            move_list_size++;
        }
        
    }

    free(piece_locations);
    return move_list_size;
}

void print_moves(struct MoveInfo *moves, int size) {
    int i;
    // printf("\nMove List:   --------------------------------------------\n");
    for (i=0; i<size;i++) {
        // printf("At: %d - Start: %d, End: %d, Piece Type: %d,  Piece Cap: %d\n", i, moves[i].start, moves[i].end, moves[i].piece_type, moves[i].piece_cap);
    }
    // printf("End Move List: --------------------------------------------\n\n");

}

void add_move(Bitboard single_move, struct MoveInfo *move_list, int move_list_size ) {
    move_list[move_list_size].move = single_move;
}

/*given a location for a move, find which moves result in a capture.
    @return:
        1 -> king
        2 -> bishop
        3 -> horse
        4 -> pawn
        0 -> no capture
*/
int check_attack(Bitboard location, struct GameBoard gm_brd, int piece_type) {
    //if a human piece
    if (piece_type <= 4 ) {
        if (location & gm_brd.comp_pieces) {
            //if attacking a computer king
            if (location & gm_brd.comp_kings) {
                return 5;
            }
            //if attacking a computer bishop
            if (location & gm_brd.comp_bishops) {
                return 6;
            }
            //if attacking a computer horse
            if (location & gm_brd.comp_horses) {
                return 7;
            }
            //if attacking a computer pawn
            if (location & gm_brd.comp_pawns) {
                return 8;
            }
        }
    } 
    //else a comp piece
    else {
        if (location & gm_brd.human_pieces) {
            //if attacking a human king
            if (location & gm_brd.human_kings) {
                return 1;
            }
            //if attacking a human bishop
            if (location & gm_brd.human_bishops) {
                return 2;
            }
            //if attacking a human horse
            if (location & gm_brd.human_horses) {
                return 3;
            }
            //if attacking a human pawn
            if (location & gm_brd.human_pawns) {
                return 4;
            }
        }

    }


    //return 0 for clearhing
    return 0;

}

void gen_computer_moves() {

}


Bitboard get_king_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd) {
    Bitboard loc = 0b01;
    loc = loc << location;
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

Bitboard get_bishop_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd) {
    Bitboard loc = 0b01;
    loc = loc << location;
    Bitboard move, left, right, uleft, uright, dleft, dright, temp;

    Bitboard diag_rl = 0b1000000001000000001000000001000000001000000001000000001000000001;
    Bitboard diag_lr = 0b1000000100000010000001000000100000010000001000000100000010000001;

    //upper left
    uleft = diag_rl >> (63 - location);
    // uleft ^= loc;

    if (uleft & gm_brd.all_pieces) {
        temp = uleft;
        Bitboard offset;
        while( temp) {
            offset = __builtin_ctzll(temp);
            temp = temp >> (offset + 1);
            temp = temp << (offset + 1);
            if (temp == 0 ) {
                uleft = 0;
                break;
            }
            if (!(temp & (gm_brd.all_pieces ^ loc))) {
                uleft = temp;
                temp = 1 << (offset);

                uleft |= temp;
                break;
            }

        }
    }

    //lower left
    dleft = diag_lr << (location);
    // dleft ^= loc;
    if (dleft & gm_brd.all_pieces) {
        temp = dleft;
        Bitboard offset;
        while( temp) {
            offset = __builtin_clzll(temp);
            temp = temp << (offset + 1);
            temp = temp >> (offset + 1);
            if (temp == 0 ) {
                dleft = 0;
                break;
            }
            if (!(temp & (gm_brd.all_pieces ^ loc))) {
                dleft = temp;
                int shift = 63 - offset;
                temp = 1;
                temp = temp << shift;

                dleft |= temp;
                break;
            }

        }
    }
    //combine upper left and down left
    left = uleft | dleft;
    // debug_board(left);
    //clear the right side


    // move |= diag_rl >> (63 - location);

    int column = location % 8;
    switch(column) {
        case 0:
            left = 0;
            right &= cl_l_b;
            break;
        case 1:
            left &= cl_r_a;
            right &= cl_l_c;
            break;
        case 2:
            left &= cl_r_b;
            right &= cl_l_d;
            break;
        case 3:
            left &= cl_r_c;
            right &= cl_l_e;
            break;
        case 4:
            left &= cl_r_d;
            right &= cl_l_f;
            break;
        case 5:
            left &= cl_r_e;
            right &= cl_l_g;
            break;
        case 6:
            left &= cl_r_f;
            right &= cl_l_h;
            break;
        case 7:
            left &= cl_r_g;
            right = 0;
            break;
    }

    //if its a human piece, only let backwards if senior
    if (invalid_locations == gm_brd.human_pieces) {

    } else {
        
    }



    move = left;
    move &= ~loc;
    move &= valid_mask;
    move &= ~invalid_locations;
    move &= bish_mask[location];
    debug_board(move);
    return move;

}
Bitboard get_horse_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd) {
    Bitboard move, clip_1, clip_2, clip_3, clip_4, clip_5, clip_6, clip_7, clip_8;
    Bitboard loc = 0b01;
    move = 0;
    loc = loc << location;

    clip_1 = clearHFile & clearGFile;
    clip_2 = clearHFile;
    clip_3 = clearAFile;
    clip_4 = clearAFile & clearBFile;
    clip_5 = clearAFile & clearBFile;
    clip_6 = clearAFile;
    clip_7 = clearHFile;
    clip_8 = clearHFile & clearGFile;

    move |= (loc & clip_4) >> 10;
    move |= (loc & clip_3) >> 17;
    move |= (loc & clip_2) >> 15;
    move |= (loc & clip_1) >> 6;

    move |= (loc & clip_5) << 6;
    move |= (loc & clip_6) << 15;
    move |= (loc & clip_7) << 17;
    move |= (loc & clip_8) << 10;

    move &= ~invalid_locations;

    return move;
}

Bitboard get_pawn_moves(int location, Bitboard invalid_locations, struct GameBoard gm_brd) {
    Bitboard loc = 0b01;
    loc = loc << location;
    Bitboard move = 0;
    Bitboard move_l = 0;
    Bitboard move_r = 0;

    //if a human pawn
    if(invalid_locations == gm_brd.human_pieces) {
        //right
        move_r |= loc >> 9;
        move_r &= clearAFile;
        move_r &= gm_brd.comp_pieces;

        //left 
        move_l |= loc >> 7;
        move_l &= clearHFile;
        move_l &= gm_brd.comp_pieces;

        //forward move
        move |= loc >> 8;
        move &= ~gm_brd.comp_pieces;
        move |= (move_r | move_l);


    //else computer pawn
    } else {
        //right
        move_r |= loc << 7;
        move_r &= clearAFile;
        move_r &= gm_brd.human_pieces;

        //left 
        move_l |= loc << 9;
        move_l &= clearHFile;
        move_l &= gm_brd.human_pieces;

        //forward move
        move |= loc << 8;
        move &= ~gm_brd.human_pieces;
        move |= (move_r | move_l);


    }
    move &= ~invalid_locations;
    return move;
}

Bitboard* get_piece_locations(Bitboard bit_brd) {
    Bitboard* p_list = malloc(100 * sizeof *p_list);
    int size = 0;
    int count = 1;

    while( bit_brd) {
        Bitboard location = __builtin_ctzll(bit_brd);
        bit_brd = bit_brd >> (location + 1);
        bit_brd = bit_brd << (location + 1);
        p_list[count] = location;
        count++;
        size++;

    }

    p_list[0] = size;
    return p_list;
}

//takes the current location of the piece
// and what piece may have been captured
// then ands it with the move bitboard in the higher bits as a header
Bitboard prepare_move_header(Bitboard move, Bitboard location, Bitboard piece) {
    debug_board(move);
    //put an int representing the what piece was captured
    piece = piece << 48;
    move = move | piece;
    //put an int representing the previous location
    location = location << 52;
    move = move | location;
    print_header(move);
    return move;
}

struct MoveInfo prepare_move(Bitboard move, int start, int end, int piece_cap, int piece_type) {
    struct MoveInfo move_info;
    move_info.move = move;
    move_info.start = start;
    move_info.end = end;
    move_info.piece_cap = piece_cap;
    move_info.piece_type = piece_type;
    return move_info;
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

void print_bits(Bitboard data) {
    int i;
    printf("Here are the bits: \n");

    Bitboard flag = 1;
    flag = flag << 63;
    for (i = 0; i < 64; i++ ) {
        if (data & flag) { 
            printf("1");
        } else {
            printf("0");
        }
        flag = flag >> 1;
    }
    printf("\n");
}

void print_header(Bitboard data) {
    int i; 
    printf("Here is the header for the board: \n");
    Bitboard flag = 1;
    flag = flag << 63;
    for (i = 0; i < 16; i++) {
        if (data & flag) { 
            printf("1");
        } else {
            printf("0");
        }
        flag = flag >> 1;
    }
    printf("\n");
}

int get_row(int location) {
    if( location <= 7) {
        return 0;
    }
    return 0;
}
