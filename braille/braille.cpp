#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>
#include"braille.h"
using namespace std;
void code(char ch, char* temp){
  switch(ch){
  case 'a':strcpy(temp,"0....."); break;
  case 'b':strcpy(temp,"00...."); break;
  case 'c':strcpy(temp,"0..0.."); break;   
  case 'd':strcpy(temp,"0..00."); break;
  case 'e':strcpy(temp,"0...0."); break;
  case 'f':strcpy(temp,"00.0.."); break;
  case 'g':strcpy(temp,"00.00."); break;
  case 'h':strcpy(temp,"00..0."); break;
  case 'i':strcpy(temp,".0.0.."); break;
  case 'j':strcpy(temp,".0.00."); break;
  case 'k':strcpy(temp,"0.0..."); break;
  case 'l':strcpy(temp,"000..."); break;
  case 'm':strcpy(temp,"0.00.."); break;
  case 'n':strcpy(temp,"0.000."); break;
  case 'o':strcpy(temp,"0.0.0."); break;
  case 'p':strcpy(temp,"0000.."); break;
  case 'q':strcpy(temp,"00000."); break;
  case 'r':strcpy(temp,"000.0."); break;
  case 's':strcpy(temp,".000.."); break;
  case 't':strcpy(temp,".0000."); break;
  case 'u':strcpy(temp,"0.0..0"); break;
  case 'v':strcpy(temp,"000..0"); break;
  case 'w':strcpy(temp,".0.000"); break;
  case 'y':strcpy(temp,"0.0000"); break;
  case 'z':strcpy(temp,"0.0.00"); break;
  }
}

int encode_character(char ch, char* braille){
  int size;
  if(isalpha(ch)){
    //lower case
    if (!isupper(ch)){
      size = 6;
      code(ch,braille);
      //braille[size] = '\0';
      return size;
    }
    //upper case
    else{
      size = 12;
      char temp[] = "....0";
      char temp1[80];
      code(tolower(ch),temp1);
      strcpy(braille,strcat(temp,temp1));
      //braille[size] = '\0';
      return size;
    }
  }


  //digit
  if(isdigit(ch) && ch != '0'){
    size = 12;
    char temp[80];
    strcpy(braille,"..0000");
    code('a'+ch-'1',temp);
    strcat(braille,temp);
    return size;
  }

  if(ch == '0'){
    strcpy(braille,"..0000.0.00.");
    return 12;
  }

  //punctuation
    if(ch == '.'){
      strcpy(braille,".0..00");
    return 6;
    }
    
    if(ch == ','){
      strcpy(braille,".0....");
    return 6;
    }
    if(ch == ';'){
      strcpy(braille,".00...");
    return 6;
    }
    if(ch == '-'){
      strcpy(braille,"..0..0");
      return 6;
    }
    if(ch == '!'){
      strcpy(braille,".00.0.");
    return 6;
    }
    if(ch == '?'){
      strcpy(braille,".00..0");
    return 6;
    }
    if(ch == '(' || ch == ')'){
      strcpy(braille,".00.00");
    return 6;
    }
  
  return 0;
}
/*
Note: debug:deal with the senel
 */
/*
void encode(const char* sentence,char* braille){
  if (*sentence == '\0'){
    *braille = '\0';
  }
  if(*sentence != '\0'){
    encode_character(*sentence,braille);
    char temp[80];
    encode(sentence+1, temp);
    strcat(braille,temp);
  }
  
}
*/

//another way
void encode(const char* sentence,char* braille){

  if (!strlen(sentence)){
  return;
    *braille = '\0';
  }
  if(*sentence != '\0'){
    encode_character(*sentence,braille);
    int size = strlen(braille);
    braille[size] = '\0';
        encode(sentence+1, braille+size);
    
  }
  
}

/*algorithm:
print line by line
 */
void print_braille(const char* sentence, ostream& out){
  char temp[80];
  // encode(sentence,temp);
  //print the kth line
  for(int k = 1; k< 4; k++){
  for(int i = 0; sentence[i] ; i++){
    encode_character(sentence[i],temp);
    out << temp[k-1] << temp[k-1+3] ;
  }
  out << "\n";
  }

  for (int i = 0; sentence[i]; i++){
    out << " " << sentence[i];
  }
  out << endl;
}
