#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */
bool valid_step(const char* current, const char* next){
  int count = 0;
  if (strlen(current) != strlen(next))
    return false;
  
  for (int i = 0; current[i]; i++){
    if (current[i] != next[i]) count ++;
  }

  if (count == 1){
    if (dictionary_search(next)) return true;
  }

  return false;
}

/*
it writes a given chain to ostream
returns true if the entire chain was writen to ostream successfully
 */
bool display_chain(const char** chain, ostream& out){
  //fail to open the file
  if (out.fail()) return false;
  
  const char** check = chain;
  bool start = true;
  //when the chain not coming to the NULL
  while(*check){
  int i = 0;
  while((*check)[i]){
    //the first one and last one should be upper case
    if (start || *(check+1) == NULL){
      char ch = toupper((*check)[i]);
      out << ch;

    } else{
      //output lower case
      char ch = tolower((*check)[i]);
      out << ch; 
    }
    i++;
    start = false;
  }
  out << '\n';
  check++; 
}
  return true;
}


bool valid_chain(const char** chain){
  bool result = true;
  const char** check = chain;
  //when the chain not coming to the end
  while(*(check+1)){
    //check the transfer from this word to next is valid or not
    bool valid = valid_step(*check,*(check+1));
    
    if (valid == false) result = false;
    check++;
  }
  //check no repetition of the words in the chain
  while(*check){
    int i =1;
    while(*(check+i)){
      if (strcmp(*check,*(check+i)) == 0) result = false;
      i++;
    }
    check++;
  }
  return result;
}

/*
Algotithm:recursive way
add another parameter index which used for record words in the chain of answer.
deal with whether it is start of the chain or not.
By loop through all the position of start and all the letter from A to Z, we need to find one temp which changes one letter from start and from temp to target, it can get from steps-1 steps.
 */
 bool find_chain(const char* start, const char* target,  const char** answer, int steps, int index){
  if (index == 0){
    *answer = start;
    *(answer+1) = NULL;
  }
  //cout << *answer << endl;
  //invalid situation
  //if (index > steps) return false;
  if (steps < 0) return false;
  if (strlen(start) != strlen(target)) return false;
  if (!dictionary_search(start)) return false;
  if(!valid_chain(answer)) return false;
  //obvious situation
  if (!strcmp(start,target)) return true;
  
  //keep continuing
  char* temp = new char[strlen(start)];
  strcpy(temp, start);
  
  int size = strlen(start);
  for (int i = 0; i < size; i++){
    char initial_ch = temp[i]; //save it in case can not find proper need to change back
    //try change from a to z in each position
    for (char ch = 'A'; ch <= 'Z'; ch++){
      temp[i] = ch;
      answer[index+1] = temp;  //note here temp is the pointer
      answer[index+2] = NULL;
      bool flag = find_chain(temp, target,answer, steps-1,index+1);
	if (flag == true){
	  return true;
      }
    }
    //if not found proper temp
    //reset the answer
    temp[i] = initial_ch;
    answer[index+1] = NULL;
  }
  delete [] temp;
  //cout << "hello" << endl;
  return false;
}

/*
debug:
1) in the function(...; steps-1) can not write as steps--
2) for one letter changed temp, need to set answer[index+1] to be new temp, which means we increase answer chain by one word
3) if not return means we didnt find , have to reset 
 */
