#include "brd.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

Bitboard CompKings    = 0b0000000000000000000110000000000000000000000000000000000000000000;
Bitboard CompBishops  = 0b0000000000000000110000000000000000000000000000000000000000000000;
Bitboard CompHorses   = 0b0000000000000000000000110000000000000000000000000000000000000000;
Bitboard CompPawns    = 0b0000000000000000000000000111111000000000000000000000000000000000;

Bitboard HumanKings   = 0b0000000000000000000000000000000000000000000000000000000000000000;
Bitboard HumanBishops = 0b0000000000000000000000000000000000000000000000000000000000000000;
Bitboard HumanHorses  = 0b0000000000000000000000000000000000000000000000000000000000000000;
Bitboard HumanPawns   = 0b0000000000000000000000000000000000000000000000000000000000000000;

char boardLayout[64] = {'-'};

Bitboard getBoard() {
    Bitboard test = 4;
    return test;
}


void printBoard() {
    //print 1st rank
    int i = 0;
    Bitboard cKings = CompKings;
    Bitboard cBishops = CompBishops;
    Bitboard cHorses = CompHorses;
    Bitboard cPawns = CompPawns;

    Bitboard hKings = HumanKings;
    Bitboard hBishops = HumanBishops;
    Bitboard hHorses = HumanHorses;
    Bitboard hPawns = HumanPawns;

    while (i < 64) {
        if (cKings & 0b01) {
            boardLayout[i] = 'K';
        } else if (cBishops & 0b01) {
            boardLayout[i] = 'B';
        } else if (cHorses & 0b01) {
            boardLayout[i] = 'H';
        } else if (cPawns & 0b01) {
            boardLayout[i] = 'P';
        }
        else {
            boardLayout[i] = '-';
        }
        cKings = cKings >> 1;
        cBishops = cBishops >> 1;
        cHorses = cHorses >> 1;
        cPawns = cPawns >> 1;
        i++;

    }
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[40],boardLayout[41],boardLayout[42],boardLayout[43], boardLayout[44], boardLayout[45], boardLayout[46], boardLayout[47]);
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[32],boardLayout[33],boardLayout[34],boardLayout[35], boardLayout[36], boardLayout[37], boardLayout[38], boardLayout[39]);
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[24],boardLayout[25],boardLayout[26],boardLayout[27], boardLayout[28], boardLayout[29], boardLayout[30], boardLayout[31]);
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[16],boardLayout[17],boardLayout[18],boardLayout[19], boardLayout[20], boardLayout[21], boardLayout[22], boardLayout[23]);
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[8],boardLayout[9],boardLayout[10],boardLayout[11], boardLayout[12], boardLayout[13], boardLayout[14], boardLayout[15]);
    printf("%c %c %c %c %c %c %c %c\n",boardLayout[0],boardLayout[1],boardLayout[2],boardLayout[3], boardLayout[4], boardLayout[5], boardLayout[6], boardLayout[7]);
    //print 2nd rank

    //print 3rd rank

    //print 4th rank

    //print 5th rank

    //print 6th rank
}

