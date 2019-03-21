#include "minimax.h"

const int MAX_DEPTH = 7;

struct MoveInfo minimax() {
    struct MoveInfo best_move;
    struct MoveScore best;
    struct MoveScore move;

    best.score = -9999;
    int gameover = 0;
    struct MoveInfo *computer_moves = malloc(1000*sizeof computer_moves);
    move.score = -9999;
    int depth = 1;

    computer_moves = gen_computer_moves(get_board());
    int size = computer_moves[0].start;
    int i;
    best.move = computer_moves[1];
    for (i=1; i<size; i++) {
        //make a move
        move.move = computer_moves[i];
        apply_move(move.move);
        move.score = min(depth+1);
        printf("move score: %d\n", move.score) ;
        if (move.score > best.score) {
            best = move;
        }
        undo_move();

    }

    free(computer_moves);
    return best.move;
}

int max(int depth) {
    struct MoveInfo best_move;
    struct MoveScore best;
    struct MoveScore move;

    best.score = -9999;
    int gameover = 0;
    struct MoveInfo *computer_moves = malloc(1000*sizeof computer_moves);
    move.score = -9999;

    if (gameover) {
        free(computer_moves);
        return 100;
    } else if (depth == MAX_DEPTH) {
        //return a call to evaluate
        free(computer_moves);
        return evaluate();
    } else {
        computer_moves = gen_computer_moves(get_board());
        int size = computer_moves[0].start;
        int i;
        for (i=1; i<size; i++) {
            //make a move
            move.move = computer_moves[i];
            apply_move(move.move);

            move.score = min(depth+1); 
            if (move.score > best.score) {
                best = move;
            }
            undo_move();

        }
        free(computer_moves);

        return best.score;
    }

}

int min(int depth) {
    struct MoveInfo best_move;

    struct MoveScore best;
    struct MoveScore move;

    best.score= 9999;
    int gameover = 0;
    struct MoveInfo *human_moves = malloc(1000*sizeof human_moves);
    move.score = 9999;

    if (gameover) {
        //gameover
        free(human_moves);
        return best.score;
    } else if (depth == MAX_DEPTH) {
        free(human_moves);
        // printf("HIT MAX DEPTH IN MIN\n");
        return evaluate();
    } else {
        human_moves = gen_human_moves(get_board());
        int size = human_moves[0].start;
        int i;
        for (i=1; i<size; i++) {
            //make a move
            move.move = human_moves[i];
            apply_move(move.move);
            move.score = max(depth+1); 
            if (move.score < best.score) {
                best = move;
            }
            undo_move();

        }
        free(human_moves);
        return best.score;
    }

}

int evaluate() {
    struct GameBoard gm_brd;
    gm_brd = get_board();
    int score = 0;
    while(gm_brd.comp_pieces) {
        if (gm_brd.comp_pieces & 0b01) {
            score++;
        }
        gm_brd.comp_pieces = gm_brd.comp_pieces >> 1;
    }
    while(gm_brd.human_pieces) {
        if (gm_brd.human_pieces & 0b01) {
            score--;
        }
        gm_brd.human_pieces = gm_brd.human_pieces >> 1;
    }
    return score;

}