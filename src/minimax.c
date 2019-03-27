#include "minimax.h"

const int MAX_DEPTH = 20;
const int MAX_VAL = 99999;
const int MIN_VAL = -99999;

struct MoveInfo ids () {
    int i;
    struct MoveScore move;
    move.score = MIN_VAL;
    struct MoveScore temp;
    printf("computer is thinking...\n");
    time_t start_time = time(0);

    for (i=1; i<=MAX_DEPTH; i++) {
        if(difftime(time(0), start_time) >= 5.0) {
            break;
        }
        printf("Searching a depth %d\n",i );
        
        temp = minimax(i, start_time);
        if (temp.score > MIN_VAL ) {
            move = temp;
        }
        if (move.score > 90000) {
            break;
        }
    }
    time_t end_time = difftime(time(0), start_time);
    int end_depth = i - 1;
    printf("Searched to a depth of: %d in %ld secs\n", end_depth, end_time);
    printf("Found move with a score of: %d\n\n\n", move.score);
    return move.move;
}

struct MoveScore minimax(int max_depth, time_t start_time) {
    struct MoveScore best;
    struct MoveScore move;

    best.score = MIN_VAL;
    struct MoveInfo *computer_moves = malloc(1000*sizeof computer_moves);
    move.score = MIN_VAL;
    int depth = 0;

    computer_moves = gen_computer_moves(get_board());
    int size = computer_moves[0].start;
    int i;
    best.move = computer_moves[1];
    for (i=1; i<size; i++) {
        //make a move
        move.move = computer_moves[i];
        apply_move(move.move);
        move.score = min(depth+1,max_depth, best, start_time);
        printf("move score: %d\n", move.score) ;
        if (move.score > best.score) {
            best = move;
        }
        undo_move();
        if(move.score > 90000 && depth <= 2) {
            best = move;
            break;
        }
        if(difftime(time(0), start_time) >= 5.0) {
            best.score = MIN_VAL;
            break;
        
        }

    }

    free(computer_moves);
    return best;
}

int max(int depth, int max_depth, struct MoveScore parent, time_t start_time) {
    struct MoveScore best;
    struct MoveScore move;

    best.score = MIN_VAL;
    int gameover = 0;
    struct MoveInfo *computer_moves = malloc(1000*sizeof computer_moves);
    move.score = MIN_VAL;

    if (gameover) {
        free(computer_moves);
        return 100;
    } else if (depth == max_depth) {
        //return a call to evaluate
        free(computer_moves);
        return evaluate(depth);
    } else {
        computer_moves = gen_computer_moves(get_board());
        int size = computer_moves[0].start;
        int i;
        for (i=1; i<size; i++) {
            //make a move
            move.move = computer_moves[i];
            apply_move(move.move);

            move.score = min(depth+1, max_depth, best, start_time); 
            if (move.score > best.score) {
                best = move;
            }
            undo_move();
            if(move.score > parent.score) {
                free(computer_moves);
                return move.score;
            }
            if(move.score > 9000) {
                best = move;
                break;
            }
            if(difftime(time(0), start_time) >= 5.0) {
                break;
            }
        }
        free(computer_moves);

        return best.score;
    }

}

int min(int depth, int max_depth, struct MoveScore parent, time_t start_time) {
    struct MoveScore best;
    struct MoveScore move;

    best.score= MAX_VAL;
    int gameover = 0;
    struct MoveInfo *human_moves = malloc(1000*sizeof human_moves);
    move.score = MAX_VAL;

    if (gameover) {
        //gameover
        free(human_moves);
        return best.score;
    } else if (depth == max_depth) {
        free(human_moves);
        // printf("HIT MAX DEPTH IN MIN\n");
        return evaluate(depth);
    } else {
        human_moves = gen_human_moves(get_board());
        int size = human_moves[0].start;
        int i;
        for (i=1; i<size; i++) {
            //make a move
            move.move = human_moves[i];
            apply_move(move.move);
            move.score = max(depth+1, max_depth, best, start_time); 
            if (move.score < best.score) {
                best = move; 
            }
            undo_move();
            if(move.score < parent.score) {
                free(human_moves);
                return move.score;
            }
            if(difftime(time(0), start_time) >= 5.0) {
                break;
            }

        }
        free(human_moves);
        return best.score;
    }

}

int evaluate(int depth) {
    struct GameBoard gm_brd;
    gm_brd = get_board();
    int score = 0;
    int piece_score = 0;
    int loc_score = 0;
    int game_status = check_game_over();
    if (game_status == 1) {
        return MAX_VAL - depth;
    }
    if (game_status == 2) {
        return MIN_VAL + depth;
    }
    Bitboard flag = 1;
    flag = flag << 47;
    int location = 47;

    // while (gm_brd.comp_kings) 
    // { 
    //   gm_brd.comp_kings &= (gm_brd.comp_kings-1) ; 
    //   piece_score += 150;
    // } 

    // while (gm_brd.comp_bishops) 
    // { 
    //   gm_brd.comp_bishops &= (gm_brd.comp_bishops-1) ; 
    //   piece_score += 10;
    //   location = __builtin_ctzll(gm_brd.comp_bishops);
    //   loc_score += location;
    // } 

    // while (gm_brd.comp_horses) 
    // { 
    //   gm_brd.comp_horses &= (gm_brd.comp_horses-1) ; 
    //   piece_score += 10;
    //   location = __builtin_ctzll(gm_brd.comp_horses);
    //   loc_score += location;
    // } 

    // while (gm_brd.comp_pawns) 
    // { 
    //   gm_brd.comp_pawns &= (gm_brd.comp_pawns-1) ; 
    //   piece_score += 5;
    // } 

    // while (gm_brd.human_kings) 
    // { 
    //   gm_brd.human_kings &= (gm_brd.human_kings-1) ; 
    //   piece_score -= 100;
    // } 
    // while (gm_brd.human_bishops) 
    // { 
    //   gm_brd.human_bishops &= (gm_brd.human_bishops-1) ; 
    //   piece_score -= 10;
    //   location = __builtin_ctzll(gm_brd.human_bishops);
    //   loc_score -= (47-location);
    // } 

    // while (gm_brd.human_horses) 
    // { 
    //   gm_brd.human_horses &= (gm_brd.human_horses-1) ; 
    //   piece_score -= 10;
    //   location = __builtin_ctzll(gm_brd.human_horses);
    //   loc_score -= (47-location);
    // } 

    // while (gm_brd.human_pawns) 
    // { 
    //   gm_brd.human_pawns &= (gm_brd.human_pawns-1) ; 
    //   piece_score -= 5;
    // } 


    while(flag) {
        if(flag & gm_brd.comp_kings) {
            piece_score += 150;
        }
        if (flag & gm_brd.comp_bishops) {
            piece_score += 10;
            loc_score += location;
        }
        if (flag & gm_brd.comp_horses) {
            piece_score += 10;
            loc_score += location;
        }
        if (flag & gm_brd.comp_pawns) {
            piece_score += 5;
            loc_score += location;
        }
        if(flag & gm_brd.human_kings) {
            piece_score -= 100;
        }
        if (flag & gm_brd.human_bishops) {
            piece_score -= 10;
            loc_score -= (47-location);
        }
        if (flag & gm_brd.human_horses) {
            piece_score -= 10;
            loc_score -= (47-location);
        }
        if (flag & gm_brd.human_pawns) {
            piece_score -= 5;
            loc_score += location;

        }
        flag = flag >> 1;
        location--;
    }

    score = (50*(piece_score-100)) + (int)(0.25*(float)loc_score) ;
    return score;

}
