#include<iostream>
#include<cstring>
#include"playfair.h"
#include<cctype>

using namespace std;

void prepare(const char* input, char* output){
  int count = 0;
  for(int i = 0; input[i]; i++){
    if(isalnum(input[i])){
	output[count]=toupper(input[i]);
	count++;
      }
  }

    if (count %2) {
      output[count] = 'X';
      output[count+1] = '\0';
    }
    else{
      output[count] = '\0';
    }
}

/*
it returns true if ch occurs before position in the string str
 */
bool occurs_before(const char* str, char ch, int position){
 
  for (int i = 0; i < position; i++){
    if (str[i] == ch) return true;
  }
  return false;
}

void renew_cord(int cordinate[2]){
  //int row = cordinate[0];
  if (cordinate[1] >= 6){
    ++cordinate[0];
    cordinate[1] = 0;
  }
  ++cordinate[1];
}

/*algprithm:
instead of using for loop for all the squares, using a new variable cordinate which is an array to document and renew it
using count to document whether come to the end of the codeword
after codeword, loop through alphbatec and number
 */
void grid(const char* codeword, char square[6][6]){
  int size = strlen(codeword);
  // cout << "size is " << size << endl;
  int count = 0;
  int cordi[2]= {0,0};
  while(count < size){
    int row = cordi[0];
    int col = cordi[1];
    if (!occurs_before(codeword, codeword[count],count)){
      square[row][col] = codeword[count];
      renew_cord(cordi);
    }
    count++;
  }
  //at end count will be the strlen(codeword)
  cout <<"count is " << count << endl;
  //fill in from A to Z
  for (char ch = 'A'; ch <= 'Z' ; ch ++){
    if (!occurs_before(codeword, ch,size)){
	square[cordi[0]][cordi[1]] = ch;
	renew_cord(cordi);
      }
  }

    //fill from 1 to 9
    for (char ch = '0'; ch <= '9'; ch ++){
      if (!occurs_before(codeword, ch,size)){
	square[cordi[0]][cordi[1]] = ch;
	renew_cord(cordi);
      }
    }

}

int find_row(const char square[6][6], char ch){
  for (int i = 0; i < 6; i++){
    for (int j = 0; j < 6; j++){
      if (square[i][j] == ch) return i;
    }
  }
  return -1;
}

int find_col(const char square[6][6], char ch){
   for (int i = 0; i < 6; i++){
    for (int j = 0; j < 6; j++){
      if (square[i][j] == ch) return j;
    }
  }
   return -1;
}

/*
Note: debug here
have to pass reference of out1 and out2 ; otherwise whhen the function closed, the out1 and out2 qon't be documented
 */
void bigram(const char square[6][6], char char1, char char2, char &out1, char &out2){
  //first find col, row fro char1 and char2
  int row1=find_row(square, char1);
  int col1=find_col(square,char1);
  int row2= find_row(square,char2);
  int col2 = find_col(square,char2);
  //cout << row1 << col1 << row2 << col2 << endl
  out1 = square[row1][col2];
  //cout << "out1 " << out1 << endl;
  out2 = square[row2][col1];
}

/*
Note : did it in a recursive way
Debug: if strlen(prepared) = 0 which means come to the end of the string, has to add '\0' to close the string
 */

void encode(const char square[6][6], const char* prepared, char* encoded){
  if(strlen(prepared)){
      char out1,out2;
      char char1 = *prepared;
      char char2= *(prepared+1);
      bigram(square,char1,char2,out1,out2);
      *encoded = out1;
      *(encoded+1) = out2;
      encode(square,prepared+2,encoded+2);
    }
  else{
  *encoded= '\0';
  }
}

//bunus question
//Note that , "CO" encode as "FK" and encode again will turn into "CO"
void decode(const char square[6][6], const char* encoded, char* decoded){
  encode(square,encoded,decoded);
}


