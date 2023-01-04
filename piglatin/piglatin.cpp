#include<iostream>
#include<cstring>
#include<fstream>
#include<cctype>
#include"piglatin.h"
using namespace std;

int findFirstVowel(const char* word){
  //find first aeiouy
  bool flag = false;
  int size = strlen(word);
  int position;
  char ch = tolower(word[0]);
  if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
    return 0;
  }
  for (int i = 1; i< size-1; i++){
    char ch = tolower(word[i]);
    if (flag == false){
      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y')
      flag = true;
      position = i;
    }
  }
  
  if (flag == true) return position;
//last one
  ch = tolower(word[size-1]);
  if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
    {
      return size-1;
    }
  return -1;
}

void translateWord(const char* english, char* piglatin){
  int position =findFirstVowel(english);
  char english1[80];
  strcpy(english1,(english));
  //starts with digit then leave it
  if (isdigit(english[0])){
      strcpy(piglatin,english);
      return;
    }
  if (position == 0){
    strcpy(piglatin,strcat(english1,"way"));
    
  }

  char temp[80];
  char temp1[80];
  if (position == -1){
    strcpy(piglatin, strcat(english1,"ay"));
	 
  }

  
  for (int i = 0; i < position; i++){
    temp[i] = tolower(english1[i]);
  }
    temp[position] = '\0';
   
    for(int i = position; english1[i]; i++){
      temp1[i-position]= tolower(english1[i]); 
    }
    /*note: debug
for temp1, it has to start from 0, although enlish starts from position
lower case the first character 
     */
    temp1[strlen(english)-position] = '\0';
    //cout << temp1 << endl;
    strcat(temp1,temp);
    strcat(temp1,"ay");
    strcpy(piglatin,temp1);

    piglatin[0]= toupper(piglatin[0]);
}

/*algorithm:
do it in a recursive way
for to character from input sources we have to deal with the situation whether we read punctuation or not
*/
void translateStream(ifstream& in, ostream& out){ 
  char english[80];
  char temp[80];
  int i = 0;
  //find the fisrt word in text
  while(isalnum(in.peek())){
    english[i]=in.get();
    i++;
  }
  english[i] = '\0';
 
  translateWord(english,temp);
  out << temp;
  //if deal with punctuation
  while(!isalnum(in.peek())){
      if (in.eof()){
	return;
      }
      out <<(char) in.get();
    }

    translateStream(in,out);
}
