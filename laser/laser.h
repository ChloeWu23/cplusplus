# pragma once
int const MAXLEN = 512;


/* pre-supplied function and type declarations */

char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **array, int rows);
char **load_board(const char *filename, int &height, int &width);
void print_board(char **board, int height, int width);

enum Direction {NORTH, EAST, SOUTH, WEST};

/* add your own function and type declarations here */

/**
 * Q1, scans the leftmost column of board for the character ’>’
 * @param board 2d char board
 * @param height height of board
 * @param width width of board
 * @param row ourput row of '>'
 * @return true if can find, false otherwise
 * */
bool find_laser(char** board, int height, int width, int& row);

/**
 * Q2 return the alphabetical character label (if any) 
 * attached to the mirror found at coordinates (row, column)
 * @param board 2d char board
 * @param height height of board
 * @param width width of board
 * @param row row to find a label
 * @param column column of a label
 * @return label char if found, '\0' otherwise
 * */
char mirror_label(char** board, int height, int width, int row, int column);

/**
 * Q3 plots the path of the laser beam across the given board, 
 * update board and output string message 
 * @param board 2d char board
 * @param height height of board
 * @param width width of board
 * @param message the output string message
 * @param last_row the final row of the laser beam
 * @param last_col the final col of the laser beam
 * @return true if and only if the final coordinates of 
 * the laser beam correspond to the laser light absorber, 
 * false otherwise
 */
bool shoot(char** board, 
           int height, 
           int width, 
           char* message, 
           int& last_row, 
           int& last_col);

/* helper fucntion for Q3
responsible for modify the direction, current row and col */
bool move_step(char** board, 
               int height, 
               int width, 
               Direction& dir, 
               int& row, 
               int& col);
/* helper fucntion for Q3 chaneg direction */
void change_direction(Direction& dir, char change);


/**
 * Q4, solve board recursively
 * @param board 2d char board
 * @param height height of board
 * @param width width of board
 * @param target, the target string to find
 * @return true of can find target string, false otherwise
 */
bool solve(char** board, int height, int width, char const* target);

/* helper fucn for Q4 */
void copy_board(char** destination, char** source, int height, int width);


