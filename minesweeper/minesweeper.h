enum MoveResult { INVALID_MOVE=-3, REDUNDANT_MOVE=-2, BLOWN_UP=-1, SOLVED_BOARD=1, VALID_MOVE=0 };

void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
void initialise_board(char board[9][9]);
bool is_complete(const char mine[9][9], const char revealed[9][9]);
int count_mines(const char* position, const char mines[9][9]);
MoveResult make_move(const char* position, const char mines[9][9],char revealed[9][9]);
bool find_safe_move(const char revealed[9][9], char* move);
void solve_board(char const mines[9][9], 
                 char revealed[9][9], 
                 char* moves);
int flag_num_around(char const * const  position, char const revealed[9][9]);
int uncovered_num_around(char const * const  position, char const revealed[9][9]);
