#include <iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>
#include "spell.h"

using namespace std;

//const int Max_Length = 80;
/* insert your function definitions here */

int frequency(const char* target){
  ifstream in;
  in.open("words.dat");
  if (in.fail()) return -1;
  char words[Max_Length]; //buffer
  int number;
  //while(in.good()) {..} is the same
  while(!in.eof()){
    in >> number >> words;
    if (/*in.good() && */strcmp(words, target) == 0){
      in.close();
      return number;
    }
  }

  in.close();
  return 0;

}

int edit_distance(const char* a, const char* b){
  int length_a = strlen(a);
  int length_b = strlen(b);
  return edit_distance(a,b,length_a, length_b);

}

int indicator(char x, char y){
  return x == y? 0: 1;
}
//overload edit_distance
int edit_distance(const char* a, const char* b, int i, int j){
  if (min(i,j) == 0)
    return max(i,j);

  if (strcmp(a,b) == 0) return 0;
  
   int out[4]= {0,0,0,0};
    
   
   //int result1,result2,result3,result4;
  //result1 = edit_distance(a,b,i-1,j)+1;
  out[0] = edit_distance(a,b,i-1,j)+1;
  // result2 = edit_distance(a,b,i,j-1)+1;
  out[1] = edit_distance(a,b,i,j-1)+1;
  //result3 = edit_distance(a,b,i-1,j-1)+ 1* (a[i-1] != b[j-1]);
  out[2] = edit_distance(a,b,i-1,j-1) + indicator(a[i-1],b[j-1]);
  if ( i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){
    //result4 = edit_distance(a,b,i-2,j-2)+1;
    out[3] = edit_distance(a,b,i-2,j-2)+1;
    //return min(min(min(result1,result2),result3),result4);
    int min_result= out[0];
    for (int k=1 ; k <4; k++){
      if (out[k] < min_result) {
	min_result = out[k];
      }
    }
    return min_result;
      }

  return min(min(out[0],out[1]),out[2]);

}


bool spell_correct(const char* word, char fixed[Max_Length]){
  ifstream in("words.dat");
  //int length = strlen(word);
  char enter[Max_Length];
  int number;
  int distance;
  int lowest_distance = Max_Length;
  /**
   *ALgorithm:
   *By checking through the dictionary, lower the lowest distance and raise most_common frequency
  then the correct one should be lowest distance and highest frequency
  **/
  int most_common = -1;
  while (!in.eof()){
    in >> number >> enter;
    distance = edit_distance(word, enter);
    if (distance == 0){
      strcpy(fixed, enter);
      in.close();
      return false;
    }

    if (distance < lowest_distance){
      lowest_distance = distance;
      most_common = number;
      strcpy(fixed, enter);
    } else if(distance == lowest_distance){
      if (number >most_common){
	most_common = number;
	strcpy(fixed, enter);
      }
    }
  }
  
    if (most_common >=0) {
      in.close();
      return true;
    }
    
  
  in.close();
  return false;
}



/*
int edit_distance_bonus(const char* a, const char* b){
  //int length_a = strlen(a);
  //int length_b = strlen(b);
  

}
*/
/**
//command
$less words.dat //show less rows of the file
$more words.dat
 **/
