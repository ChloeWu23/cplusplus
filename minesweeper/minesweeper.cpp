#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "minesweeper.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load mine positions from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || buffer[n] == '*' || buffer[n] == ' ' || buffer[n] == '?' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << "|";
  for (int i=0; i<9; i++) 
    cout << ( (data[i]=='.') ? ' ' : data[i]);
  cout << "|" << endl;
}

/* pre-supplied function to display a minesweeper board */
void display_board(const char board[9][9]) {
  cout << "  ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r);
  cout <<  endl;
  cout << " +---------+" << endl;
  for (int r=0; r<9; r++) 
    print_row(board[r],r);
  cout << " +---------+" << endl;
}

/* pre-supplied function to initialise playing board */ 
void initialise_board(char board[9][9]) {
  for (int r=0; r<9; r++)
    for (int c=0; c<9; c++)
      board[r][c] = '?';
}

/* add your functions here */
bool is_complete(const char mines[9][9],const char revealed[9][9]){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      //if have mines check been solved or not
      if (mines[i][j] == '*'){
	if ( revealed[i][j] == '?')
	  return false;
	
      }
    }
  }

  return true;

}


int count_mines(const char* position, const char mines[9][9]){
  int row = position[0] - 'A'; //row starts with 0
  int col = position[1] - '1';//col starts with 0
  int count = 0;
  //check adjacent position has mines or not
  for (int i = -1; i <= 1; i++){
    for ( int j = -1 ; j <= 1; j++){
      //valid position
      int k = row+i;
      int l = col +j;
      if ( k >= 0 && k <=8 && l>= 0  && l <=8){
   
	if (mines[k][l] == '*') count++;
	
      }

    }
  }
  //exclude itself
  if (mines[row][col] == '*') count--;
  return count;
}

/*
Debug here: since revealed[r][c] is char, count is int can not put it into directly, count+ '0' instead
Debug here: for blow up have to add condition of size = 2 which means to uncover
Debug: return solved_board have to put on the last
Algorithm: if this position is a valid move and count = 0 means no mines around thus we can move to all consective position to uncover more
*/
MoveResult make_move(const char* position, const char mines[9][9], char revealed[9][9]){
  int row = position[0] - 'A';
  int col = position[1] - '1';
  char ch;
  int size = strlen(position);
  if (size >2){
    ch = position[2];
  }
 
  //invalid move
  if (row <0 || row > 8 || col < 0 || col > 8){
    return INVALID_MOVE;
  }

  if(size >2 && ch != '*'){
    return INVALID_MOVE;
  }
  //redundant move:this position has been revealed or flaged
  if(revealed[row][col]=='*' || isdigit(revealed[row][col]))
    return REDUNDANT_MOVE;

  //blown_up:uncover a mines
  if (mines[row][col] == '*' && size ==2)
    return BLOWN_UP;


  //else,valid move and change the revealed board
  if (size > 2){
    //put flag on the revealed
    revealed[row][col] = '*';
  }else{
  //reveal the digit
    int count = count_mines(position,mines);
    if (count > 0) revealed[row][col] = count + '0';
    else {
    revealed[row][col] = ' ';
    char temp[2];
    //do recursion here, since no mints around so move to all posible position around;
    for (int i = -1; i <= 1; i++){
      for ( int j = -1 ; j <= 1; j++){
	//valid position
	int k = row+i;
	int l = col +j;
	if ( k >= 0 && k <=8 && l>= 0  && l <=8){
	  //debug: add condition for this new position havent been revealed thus we do recursion
	  if(revealed[k][l] == '?'){
	  temp[0] = k+'A';
	  temp[1]= l+'1';
	  temp[2] = '\0';
	  make_move(temp,mines,revealed);//did recursion here
	  }
	}
      }
    }
    }
  }

  //solved_board: all non-mine squared in revealed has been uncovered
  if (is_complete(mines,revealed)){
    return SOLVED_BOARD;
    }
  
  return VALID_MOVE;
}


int flag_num_around(char const * const  position, char const revealed[9][9]) {
    int count = 0, pos[2];
    pos[0] = position[0] - 'A';
    pos[1] = position[1] - '1';
    // i, j for displacement(-1,0,1) in row and col
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (pos[0] + i >= 0 && pos[0] + i < 9 &&
                pos[1] + j >= 0 && pos[1] + j < 9 &&
                (i || j) && 
                revealed[pos[0] + i][pos[1] + j] == '*') {++count;}
        }
    }
    return count;
}


int uncovered_num_around(char const * const  position, char const revealed[9][9]) {
    int count = 0, pos[2];
    pos[0] = position[0] - 'A';
    pos[1] = position[1] - '1';
    // i, j for displacement(-1,0,1) in row and col
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (pos[0] + i >= 0 && pos[0] + i < 9 &&
                pos[1] + j >= 0 && pos[1] + j < 9 &&
                (i || j) && 
                revealed[pos[0] + i][pos[1] + j] == '?') {++count;}
        }
    }
    return count;
}


/*
algorithm: try from row by row, col by col find '?'and then decide we uncover or flag
safe uncover: its 3*3 matric has a position where it has mines_count i but its surronding already have ith flag(can deduce this position is not a mine from surronding
safe setflag(can deduce this position is a mine from surronding):its surronding has a pos where its mines count has i and it covered surroding has flag less than i, then this position must be a mines
*/
/*
Others solution
*/
bool find_safe_move(char const revealed[9][9], char * move) {
    int move_pos = 0;
    move[0] = '\0';
    char pos[3]; 
    pos[2] = '\0';

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // for all cell around a position
            // firstly check its surrounding 3x3 blocks
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (row + i >= 0 && row + i < 9 &&
                        col + j >= 0 && col + j < 9 &&
                        (i || j)) {
                        pos[0] = 'A' + row + i;
                        pos[1] = '1' + col + j;
                        // make sure uncovered
                        if (revealed[row][col] == '?') {
                            // safe uncover
                            if (revealed[row+i][col+j] >= '1' && 
                                revealed[row+i][col+j] <= '8' && 
                                flag_num_around(pos, revealed) == revealed[row+i][col+j]-'0') {
                                move[move_pos++] = row + 'A';
                                move[move_pos++] = col + '1';
                                move[move_pos] = '\0';
                                return true;
                            }
                            // safe flag
                            if (revealed[row+i][col+j] >= '1' && 
                                revealed[row+i][col+j] <= '8' && 
                                uncovered_num_around(pos, revealed) + flag_num_around(pos, revealed) == revealed[row+i][col+j] - '0') {
                                move[move_pos++] = row + 'A';
                                move[move_pos++] = col + '1';
                                move[move_pos++] = '*';
                                move[move_pos] = '\0';
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}



