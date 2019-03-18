#include <stdio.h>
#include <stdlib.h>

int main() {
    u_int64_t t = 0b0000000000000000000000000000000000000000000000001000000000000000;
    int zeros = __builtin_ctzll(t);
    printf("here are how many 0's %d\n", zeros);
}