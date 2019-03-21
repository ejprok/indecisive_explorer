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


struct MoveInfo minimax();

int min(int depth, struct MoveScore parent);
int max(int depth, struct MoveScore parent);
int evaluate();

#endif