#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include<cmath>
#include "common.h"
#include "mask.h"
#include "gogen.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which removes unprintable characters like carriage returns and newlines from strings */
void filter (char *line) {
  while (*line) {
    if (!isprint(*line))
     *line = '\0';
    line++;
  }
}

/* loads a Gogen board from a file */
char **load_board(const char *filename) {
  char **board = allocate_2D_array(5, 6);
  ifstream input(filename);
  assert(input);
  char buffer[512];
  int lines = 0;
  input.getline(buffer, 512);
  while (input && lines < HEIGHT) {
    filter(buffer);
    if (strlen(buffer) != WIDTH)
      cout << "WARNING bad input = [" << buffer << "]" << endl;
    assert(strlen(buffer) == WIDTH);
    strcpy(board[lines], buffer);
    input.getline(buffer, 512);
    lines++;
  }
  input.close();
  return board;
}

/* saves a Gogen board to a file */
bool save_board(char **board, const char *filename) {
  ofstream out(filename); 
  if (!out)
    return false;
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      out << board[r][c];
    }
    out << endl;
  }
  bool result = out.good();
  out.close();
  return result;
}

/* internal helper function for counting number of words in a file */
int count_words(const char *filename) {
  char word[512];
  int count = 0;
  ifstream in(filename);
  while (in >> word)
    count++;
  in.close();
  return count;
}

/* loads a word list from a file into a NULL-terminated array of char *'s */
char **load_words(const char *filename) {
  int count = count_words(filename);
  ifstream in(filename);
  assert(in);
  int n=0;
  char **buffer = new char *[count+1]; // +1 because we NULL terminate 
  char word[512];
  for (; (in >> word) && n<count; n++) {
    buffer[n] = new char[strlen(word) + 1];
    strcpy(buffer[n], word);
  }
  buffer[n] = NULL;
  in.close();
  return buffer;
}

/* prints a Gogen board in appropriate format */
void print_board(char **board) {
  for (int r=0; r<HEIGHT; r++) {
    for (int c=0; c<WIDTH; c++) {
      cout << "[" << board[r][c] << "]";
      if (c < WIDTH-1)
	cout << "--";
    }
    cout <<endl;
    if (r < HEIGHT-1) {
      cout << " | \\/ | \\/ | \\/ | \\/ |" << endl;
      cout << " | /\\ | /\\ | /\\ | /\\ |" << endl;
    }
  }
}

/* prints a NULL-terminated list of words */
void print_words(char **words) {
  for (int n=0; words[n]; n++) 
    cout << words[n] << endl;
}

/* frees up the memory allocated in load_board(...) */
void delete_board(char **board) {
  deallocate_2D_array(board, HEIGHT);
}

/* frees up the memory allocated in load_words(...) */
void delete_words(char **words) {
  int count = 0;
  for (; words[count]; count++);
  deallocate_2D_array(words, count);
}

/* add your own function definitions here */
bool get_position(char** board, char ch, int& row, int& col){
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      if (board[i][j] == ch) {
	row = i;
	col = j;
	return true;
      }
    }
  }

  row = -1;
  col = -1;
  return false;
}

/*
  algorithm:
if a word can be spell by board,
then the consecutive character has to be in one-neighbor
 */
bool valid_solution(char** board, char** words){
  //check all the position on the boards has been filled
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      if (!isalpha(board[i][j])){
	  return false;
	  }
    }
  }
  int i = 0;
  int pos[2];
  int next_pos[2];
    //check whether can spell or not
    while(words[i]){
      //in each word
      int size = strlen(words[i]);
      for (int j =0; j < size -1; j++){
	char ch = words[i][j];
	//not coming to the last one
	  get_position(board,ch,pos[0],pos[1]);
	  char ch_next = words[i][j+1];
	  get_position(board,ch_next,next_pos[0],next_pos[1]);
	  if (abs(pos[0]-next_pos[0]) > 1 || abs(pos[1]-next_pos[1]) > 1 || pos[0]== -1 || next_pos[0] == -1 ){
	    return false;
	  }
       
      }

      i++;
    }
    return true;
  }


/*
Debug here:
the board[i][j] is not empty, it wither be '.' or alphabet
*/
void update(char** board, char ch, Mask &mask){
  //first find out whether we can find ch on the board
  for (int i =0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      if (board[i][j] == ch){
	mask.set_all(false);
	//flag = true;
	mask[i][j]=true;
	return;
      }
    }
  }
  //print_board(board);
  mask.set_all(false);
  //if ch is not found on board
  for (int i = 0; i < 5; i++){
    for (int j = 0; j <5; j++){
      if(!isalpha(board[i][j])) {
	mask[i][j]=true;
      }
    }
  }

}

void neighbourhood_intersect(Mask one, Mask& two){
  Mask temp;
  temp =one.neighbourhood();
  two.intersect_with(temp);

}

/*
Algorithm: creat all the mask from A to Y
TO reduce free letters'd true of its mask: check all the words and make sure consective letters mask be intersected
After reduce freedom
check this letter on board or not, if not on board and its mask only has one true, then change it on the board and recursive to see whether can be solved by adding one letter
if its mask has more than one true, which means this letter may have more positions to put on the b oard, thus our algorithm is to try from row to row, col to col, empty space put from A to Z(satisfy this letter can be put on this position determined by mask)
*/
bool solve_board(char** board, char** words){
  //create an array of 25 masks
  Mask mask[25]; //each mask[0] is the mask for element A in board
  for (int i = 0; i < 25; i++){
    update(board,'A'+i,mask[i]);
  }

  //repeated use the adjacent letters in each word with neighbourhood_intersect and update mask
  int i = 0;
  //in each words
  while(words[i]){
    //for adjacent letters
    int size = strlen(words[i]);
    for (int j = 0; j < size-1; j++){
      //find the character of that mask
      char ch = words[i][j];
      char ch_next = words[i][j+1];
      //check for ch and ch_next is for which mask
      int num=ch-'A';
      int num_next = ch_next-'A';
      //update these two masks by doing the intersection
      neighbourhood_intersect(mask[num],mask[num_next]);   
    }
    i++;
  }

  //check boundary to see we can solve it or not:mask.count() == 0 meaans we cant place one ch on the board
  for (int i = 0; i < 25; i++){
    if (mask[i].count() == 0) {
      return false;
    }
  }

  //only one solution recursive, also need to reset the board
  //note that continue comes to the next iteration i++ without executing the following code after continue
  for (int i = 0; i < 25; i++){
    if (has_character(board, 'A'+i)){
      continue;
    }
    //find characters which are not on the board
    int row,col;
    mask[i].get_position(true,row,col);
    //only one possible solution for each
    if (mask[i].count() == 1 && board[row][col] == '.'){
	//reset board[row][col]
        board[row][col] = 'A'+i;
	//cout << board[row][col] << endl;
	//recursive
	if (!solve_board(board,words)){
	  //cout << "here1" << endl;
	  board[row][col] = '.';
	}else{
	  break; //jump out of the loop of iteration i
	}
      }
  }

  //more solution recursive
  //guess one position row by row, col by col from character A
  //guess from character A+i
  
  for (int i = 0 ; i < 25; i++){
    if (has_character(board,'A'+i)){
      continue;
    }
    for (int row = 0; row < 5; row++){
      for (int col = 0; col < 5; col++){
	//check whether can put character A+i on this row,col on the board, which means mask of this character has to be true
	if (mask[i].count() > 1 && mask[i][row][col]){
	  board[row][col] = 'A'+i;
	  //recursive to see whether we change this spot the puzzle can be solved or not
	  if (!solve_board(board,words)){
	      //reset
	      board[row][col] = '.';
	    }else{
	      break;
	    }
	}
      }
    }
  }
 
    //update mask
  for (int i = 0; i <25; i++){
      update(board,'A'+i,mask[i]);
  }
    //check to see whether each mask count is 1
    for (int i = 0; i < 25; i++){
      if (mask[i].count() != 1) return false;
    }

  
  return true;

}

  bool has_character(char** board, char ch){
    for (int i = 0; i <5; i++){
      for (int j = 0; j < 5; j++){
	if (board[i][j] == ch) return true;
      }

    }
    return false;
  }
