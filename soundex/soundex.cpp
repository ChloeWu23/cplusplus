#include<iostream>
#include<cctype>
#include<cstring>
#include"soundex.h"
using namespace std;
/* Function defination */
void encode(const char* surname, char* soundex){
  soundex[0] = toupper(surname[0]);
  int count = 1;
  for (int j=1; surname[j]; j++){
    if (count == 1) {
      if (code(surname[j]) >= '1' && code(surname[j]) <='6') {
	soundex[count] = code(surname[j]);
	count++;
      }
    } else{
      if (code(surname[j]) >= '1' && code(surname[j]) <='6' && code(surname[j]) != soundex[count-1]) {
	soundex[count] = code(surname[j]);
	count++; 
      }
    }
  }

  //check whether need to add '0'
  for (int i = count; i < 4; i++)
    soundex[i] = '0';

  soundex[4] = '\0';
}

char code(char letter){
  if (letter == 'b' || letter == 'f' || letter == 'p' || letter =='v')
    return '1';
  if (letter == 'c' || letter == 'g' || letter == 'j' || letter =='k' || letter == 'q' || letter == 's' || letter == 'x' || letter == 'z')
    return '2';
  if (letter == 'd' || letter == 't')
    return '3';

  if (letter == 'l')
    return '4';

  if (letter == 'm' || letter == 'n')
    return '5';

  if (letter == 'r')
    return '6';

  return '0';

}

bool compare(const char* one, const char* two){

  if (*one == '\0' && *two == '\0'){
    return true;
  }
  if ( *one == *two)
    return compare(one+1,two+1);

  return false;
}

int count(const char* surname, const char* sentence){
   char soundex[5],soundex1[5];
  int count = 0;
  char sentence1[80];
  strcpy(sentence1,sentence);
  //cout << sentence1;
  encode(surname,soundex);
  char* token = strtok(sentence1, ", "); //delim is comma followed by empty space
  while(token != NULL){
    encode(token,soundex1);
    if(compare(soundex,soundex1)) count++;
    //NULL indicates we are using the same pointer we used previously
    token = strtok(NULL, ", ");
  }
 
  return count;
}
