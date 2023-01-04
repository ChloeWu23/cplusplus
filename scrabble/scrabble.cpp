#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"

using namespace std;

/* insert your function definitions here */
int tile_score(char tile){
  if (tile >= 'a' && tile <= 'z')
    tile = toupper(tile);
  if (tile == 'A' || tile == 'E' || tile == 'I' || tile == 'L' || tile == 'N'
      || tile == 'O' || tile =='R'|| tile == 'S' || tile == 'T' || tile == 'U' )
    return 1;
  
  if (tile == 'D' || tile == 'G' )
    return 2;

  if (tile == 'C' || tile == 'B' || tile == 'M' || tile == 'P')
    return 3;

  if (tile == 'F' || tile == 'H' || tile == 'V' || tile == 'Y' || tile == 'W')
    return 4;
  
  if (tile == 'K')
    return 5;
  
  if (tile == 'J' || tile == 'X' )
    return 8;
  if (tile == 'Z' || tile == 'Q' )
    return 10;

  if(tile==' ' || tile == '?')
    return 0;
  return -1;
}



bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles){

  if(can_form_word_from_tiles(word,tiles))
    {
      // int flag_count = 0;
      int length = strlen(word);
      for (int i = 0; word[i]; i++){
	bool flag = false;
	for(int j = 0; j < i ; j++){
	  if (word[j] == word[i]) flag = true;
	}
	if (flag == true ) played_tiles[i] = '?';
	else { played_tiles[i] = word[i];}
      }
      played_tiles[length] = '\0';
      return true;
      }
    
  return false;
}

bool can_form_word_from_tiles(const char* word, const char* tiles){
  int flag_count = 0;
  if (strlen(word) == 0) return true;
  if (is_repeat(*word,word+1)) {
    return can_form_word_from_tiles(word+1,tiles) && flag_count == 0;
  }else{
    return is_included(*word,tiles,flag_count) && can_form_word_from_tiles(word+1,tiles);
  }
  return false;
}

  bool is_repeat(char letter,const char* word){
    for (int i = 0; word[i];i++){
      if (word[i] == letter) return true;
    }
    return false;
  }

bool is_included(char letter, const char* tiles, int &flag_count){
  for(int i = 0; tiles[i]; i++){
    if (tiles[i] == letter)
      //flag_count++;
      return true;
  }
  
  for (int i = 0; tiles[i]; i++)
    if (tiles[i] == ' ' || tiles[i] == '?'){
      flag_count++;
      return true;
    }
  return false;
}
