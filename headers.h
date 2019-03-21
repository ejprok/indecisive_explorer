#include "src/brd.h"
#include "src/mv_gen.h"
#include "src/minimax.h"

void get_which_player();
void ask_which_player();
void game_loop();
void check_game_over();
void human_move();
void computer_move();
char* convert_index_to_str(int input);
char* get_user_move();
int check_valid_input(char* input, char** move_string_list, int list_size);
void apply_move( struct MoveInfo move);
void undo_move();
void print_game_history();