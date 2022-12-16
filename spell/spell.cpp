#include <iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>
#include "spell.h"

using namespace std;

const int Max_Length = 80;
/* insert your function definitions here */

int frequency(const char* target){
  ifstream in;
  in.open("words.dat");
  if (in.fail()) return -1;
  while(!in.eof()){
     char words[Max_Length];
    int number;
    in >> number >> words;
    if (strcmp(words, target) == 0)
      return number;
  }

  in.close();
  return 0;

}

int edit_distance(const char* a, const char* b){
  int length_a = strlen(a);
  int length_b = strlen(b);

  return edit_distance(a,b,length_a, length_b);

}


int edit_distance(const char* a, const char* b, int i, int j){
  if ( min(i,j) == 0)
    return max(i,j);

  if (strcmp(a,b) == 0) return 0;
  int result1,result2,result3,result4;
  result1 = edit_distance(a,b,i-1,j)+1;
  result2 = edit_distance(a,b,i,j-2)+1;
  result3 = edit_distance(a,b,i-1,j-1)+ 1* ( a[i-1] != b[j-1]);

  if ( i > 1 && j > 1 && a[i-1] == b[j-2] && a[i-2] == b[j-1]){
    result4 = edit_distance(a,b,i-2,j-2)+1;
    return min(min(min(result1,result2),result3),result4);
      }

  return min((min(result1,result2),result3),result4);

}
