#ifndef _MX_
#define _MX_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "brd.h"
#include "mv_gen.h"
#include "../headers.h"

struct MoveScore
{
    struct MoveInfo move;
    int score;
};


struct MoveInfo ids();
struct MoveInfo minimax(int max_depth, time_t start_time);

int min(int depth, int max_depth, struct MoveScore parent, time_t start_time);
int max(int depth, int max_depth, struct MoveScore parent, time_t start_time);
int evaluate(int depth);

#endif