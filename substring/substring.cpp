#include<iostream>
#include<cstring>
#include"substring.h"
using namespace std;

/*Function Definition*/
/**
Note that is_prefix function returns true wheh string a is prefix of b, is not prefix of this
 **/
bool is_prefix(const char* a, const char* b){
  //if string a is empty, then it must be prefix of b
  if (*a == '\0') return true;
  //if string b is shorter than a ,a cant be its prefix
  if (strlen(b) < strlen(a)) return false;
  //cout << "hello";
  if ( *a == *b){
    return is_prefix(a+1,b+1);
  }
 
  return false;

}


int substring_position(const char* a, const char* b){
  //if a is substring of b
  int count = 0;
  int length_a = strlen(a);
  int length_b = strlen(b);
  if (length_b < length_a) return -1;
  if (length_a == 0) return 0;
  
  for( int i = 0; i <= length_b; i++){
    if (*(b+i) != *a) count++;
    else{
    //fisrt element of a is find in string b
    if (is_prefix(a,b+i)) return count;
	else count++;
    }
  }
  

  return -1;
}

//bonus:
//strstr(const char* string, const cahr* target)
int substring_position2(const char* a, const char* b){
  return a? (strstr(b,a)?strstr(b,a)-b :-1) :0; 
}
