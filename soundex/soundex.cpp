#include<iostream>
#include<cctype>
#include<cstring>
#include"soundex.h"
using namespace std;
/* Function defination */
/*
Note that add sentiel once we add a character in s c_string
*/
/*
void encode(const char* surname, char* soundex){
  strcpy(soundex,"");
  soundex[0] = toupper(surname[0]);
  soundex[1] = '\0';
  int count = 1;
  for (int j=1; surname[j]; j++){
    if (count == 1) {
      if (code(surname[j]) >= '1' && code(surname[j]) <='6') {
	soundex[count++] = code(surname[j]);
	//count++;
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

*/
//debug: additional letters should be ignored
/*TO make the logic more elegent*/
void encode(const char* surname, char* soundex){
  strcpy(soundex,"");
  int count = 0;
  soundex[count++] = toupper(surname[0]);
 
  for (int j=1; surname[j]; j++){
    if (count <= 4){
    if (code(surname[j]) == '0') {
      //cout << "should ignore" << endl;
      continue; //out of the loop of j
    }
  //here code(.) is 1 to 6
  if (count == 1){
    soundex[count++] = code(surname[j]);
  }
  //count larger than 1
    if (code(surname[j]) == soundex[count-1]){
      continue;
    }else{
      soundex[count++] = code(surname[j]);
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
//strtok() is not good since the last one end with "."  not ", "

/*
Debug here: when to end the word, by comma or . or empty space
*/
int count(const char* surname, const char* sentence){
  char str[80];
  strcpy(str,"");
  int count = 0;
  int num = 0;
  char soundex[80], soundex1[80];
  encode(surname,soundex);
  cout << soundex << endl;
  for (int i = 0; sentence[i]; i++){
    if(isalpha(sentence[i])) {
      str[count++] =sentence[i];
    }
    
    if(sentence[i] == ','|| sentence[i] == '.' || sentence[i] == ' '){
      //terminate the str
      str[count] = '\0';
      //cout << str << endl;
      encode(str,soundex1);
      cout << soundex1 << endl;
      if (compare(soundex,soundex1)) num++;
      count = 0;
    }
 

  }

  return num;
}

//others solution
/*
int count(char const * surname, char const * sentence) {
    int count = 0;
    char sd1[5], sd2[5];
    std::string word = "";
    // split words from a sentence
    for (size_t i = 0; i < strlen(sentence); ++i) {
        if (!isalpha(sentence[i])) {
            encode(surname, sd1);
            encode(word.c_str(), sd2);
            if (compare(sd1, sd2)) {++count;}
	    cout << sd2 << endl;
            word = "";
        }
        else {word += sentence[i];}
    }
    return count;
}
*/
