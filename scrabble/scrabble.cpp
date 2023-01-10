#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include "scrabble.h"
#include<algorithm>
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



/*
ALgorithm:
convert const char* tiles to string, then it can search the repeated or space from front to end and it can also modify the tiles. after modifying, converting back by using str.c_str()

Note thaT: Once we found the charactetr from word in the tiles we have to remove it from tiles
*/

/*
bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles){
  //string word_ = word;
  string tiles_ = tiles;
  if (strlen(word)==0){
    *played_tiles = '\0';
    return true;
  }

  auto it = find(tiles_.begin(),tiles_.end(), *word);
  auto question =find(tiles_.begin(),tiles_.end(), '?');
  auto space = find(tiles_.begin(),tiles_.end(), ' ');

  if (it != tiles_.end()){
    //word_=word.substr(1);//it starts from position 1 and ends to the end of the string
    word++;
    *played_tiles = *it;
    tiles_.erase(it);
    const char* tiles1=tiles_.c_str();
    return can_form_word_from_tiles(word,tiles1,++played_tiles);
  }
  else if (space !=tiles_.end()){
    //word_ = word.substr(1);
    word++;
    *played_tiles = *space;
    tiles_.erase(space);
    const char* tiles1=tiles_.c_str();
    return can_form_word_from_tiles(word,tiles1,++played_tiles);
  }else if (question !=tiles_.end()){
    // word_ = word.substr(1);
    word++;
    *played_tiles = *question;
    tiles_.erase(question);
    const char* tiles1=tiles_.c_str();
    return can_form_word_from_tiles(word,tiles1,++played_tiles);
  }else{
    return false;
  }
}
*/

/*another way: dont use include<algorithm> */
bool can_form_word_from_tiles(const char* word, const char* tiles, char* played_tiles){
  char tiles1[80]; //this is used to change for recursion
  strcpy(tiles1,tiles);
  if (!*word){
    return true;
  }
  
  char ch = toupper(*word);
  //find whether we can get ch in the tiles, if we can change this position of the tiles to be 0
  for (int i = 0; tiles1[i]; i++){
    if (ch!=tiles1[i]){
      continue;
    }
      *played_tiles = ch;
      *(played_tiles+1) = '\0';
      //cout << "played_tiles " << played_tiles << endl;
      tiles1[i] = '0';
      //cout << "changed tiles1 is " << tiles1 << endl;
      return can_form_word_from_tiles(word+1,tiles1,played_tiles+1);
  }
  
 
  //if not found this character in the tiles then we can find ? or space
  
    for (int i = 0; tiles1[i]; i++){
      if (tiles1[i] == '?' || tiles1[i] == ' '){
	*played_tiles = '?';
	*(played_tiles+1) = '\0';
	tiles1[i] = '0';
	return can_form_word_from_tiles(word+1,tiles1,played_tiles+1);
      }
    }
    
 
     return false;
}
/*
Note: debug here,
1) if we pass an enum varible to a function, we better pass pointer to the enum thus we can refer to element of the array
2) we assume played_tiles can be formed from tiles provided, thus once its length is 7 then it use up all the tiles
*/
int compute_score(const char* played_tiles, ScoreModifier* sm){
  int score = 0;
  bool flag_double = false;
  bool flag_tripple = false;
  //bool end = false;
  for ( int i = 0; played_tiles[i]; i++){
    int num = tile_score(played_tiles[i]);
    if (sm[i] == NONE){
      //num = num;
      score += num;
    }

    if (sm[i] == DOUBLE_LETTER_SCORE){
      num *= 2;
      score += num;
    }

    if (sm[i] == TRIPLE_LETTER_SCORE){
      num *= 3;
      score += num;
    }

    if (sm[i] == DOUBLE_WORD_SCORE){
      flag_double = true;
      score += num;
    }

    if (sm[i] == TRIPLE_WORD_SCORE){
      flag_tripple = true;
      score+= num;
    }
  }

  if (flag_double == true) score *= 2;
  if (flag_tripple == true) score *= 3;
  
  //test whether all the tiles has been used
  if (strlen(played_tiles) ==7)
    score += 50;
  return score;
}


/* 
Algorithm: open the file search for all the words and can see whether can make from tiles and calculate and compare the scores
 */
int highest_scoring_word_from_tiles(const char* tiles, ScoreModifier* sm, char* word){
  int score = 0;
  ifstream in;
  in.open("words.txt"); //debug, dont forget open the file first
  char temp[80];
  char word_temp[80];
  if (in.fail()){
    cerr << "can not open the file" << endl;
  }
  while(!in.eof()){
    //bool flag = false;
    int num;
    in >> temp;
    //if it can be formed from tiles
    if (can_form_word_from_tiles(temp,tiles,word_temp)){
      num = compute_score(word_temp,sm);
      if (num > score){
	score = num;
	strcpy(word,word_temp);
      }
    }
  }

  //if no words can be formed
  if (score == 0) return -1;

  return score;
}
