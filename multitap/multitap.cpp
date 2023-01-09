#include<cstring>
#include<iostream>
#include"multitap.h"
#include<cctype>
#include<fstream>

using namespace std;

int encode_character(char ch, char* str){
  //neglect cases of lower or upper
  //int size = 0;
  //digit
  if (isdigit(ch)){
    *str='*';
    str[1] = ch;
    str[2] = '\0';
    
  }

  //if its punctuation
  if (ch == '.'){
    strcpy(str,"1");
    return 1;
  }

  if (ch == ','){
    strcpy(str,"11");
    return 2;
  }

  if (ch == '!'){
    strcpy(str,"111");
    return 3;
  }
  if (ch == '?'){
    strcpy(str,"1111");
    return 4;
  }
  if (ch == ' '){
    strcpy(str,"0");
    return 1;
  }


  //if its alphabet
  if(isalpha(ch)){
    ch = tolower(ch);
    switch(ch){
    case 'a': strcpy(str,"2"); break;
    case 'b': strcpy(str,"22"); break;
    case 'c': strcpy(str,"222"); break;
    case 'd': strcpy(str,"3"); break;
    case 'e': strcpy(str,"33"); break;
    case 'f': strcpy(str,"333"); break;
    case 'g': strcpy(str,"4"); break;
    case 'h': strcpy(str,"44"); break;
    case 'i': strcpy(str,"444"); break;
    case 'j': strcpy(str,"5"); break;
    case 'k': strcpy(str,"55"); break;
    case 'l': strcpy(str,"555"); break;
    case 'm': strcpy(str,"6"); break;
    case 'n': strcpy(str,"66"); break;
    case 'o': strcpy(str,"666"); break;
    case 'p': strcpy(str,"7"); break;
    case 'q': strcpy(str,"77"); break;
    case 'r': strcpy(str,"777"); break;
    case 's':strcpy(str,"7777");break;
    case 't': strcpy(str,"8"); break;
    case 'u': strcpy(str,"88"); break;
    case 'v': strcpy(str,"888"); break;
    case 'w': strcpy(str,"9"); break;
    case 'x': strcpy(str,"99"); break;
    case 'y': strcpy(str,"999"); break;
    case 'z':strcpy(str,"9999");break;
    }
  }

  return strlen(str);
}


void encode(const char* plaintext, char* str){
  strcpy(str, "");
  //start with first element in plaintext
  //check whether it is upper case and whether add '|' or not
  int count= 0;
  //  bool lower = true;
  while(plaintext[count]){
    //int  i = count;
    char ch = plaintext[count];
    //check whether we need to add '#'
    if (count == 0 && isupper(ch)){
      strcat(str,"#");
    }
    if (count > 0){
      char ch_last = plaintext[count-1];
      if (islower(ch_last) != islower(ch) &&isalpha(ch_last) && isalpha(ch)){
	strcat(str, "#");
      }
    }
    //add encode of this character
    char temp[80];
    if (isalpha(ch)){
      encode_character(tolower(ch),temp);
      strcat(str,temp);
    } else{
      encode_character(ch,temp);
      strcat(str,temp);
    }
      //test whether we need to add '|'
    if (plaintext[count+1]){
    int size = strlen(str); 
    char temp1[80];
    char ch_next = plaintext[count+1];
    encode_character(ch_next,temp1);
    //cout << "last code of this character" << str[size-1] << endl;
    if (str[size-1] == *temp1){
      //cout << "*temp" << *temp1 << endl;
      strcat(str, "|");
    }
    }
    count++;
  }
  
}
/*
void decode(ifstream& in, ostream& out){
  char ch,ch_next;
char n;
string temp;
  //when to stop:3 situation
  while(!in.eof()){
    ch = in.peek();
    if(ch == '#' || ch == '|'){
    in.get(n);
    ch = in.get();
    ch_next=in.get();
//check when to stop
      while(ch_next != '#' && ch_next != '|' && ch != ch_next){
      temp += ch_next;   
      }
    } else{
    ch = in.get();
temp =ch;
    ch_next = in.get();
    //check when to stop
    while(ch_next != '#' && ch_next != '|' && ch != ch_next){
    temp += ch_next;   
    }
    }

out << decode(temp.c_str());
}
}
*/


char decode(char* str){
  //for digit
  if (*str == '*') return str[1];
  if(!strcmp(str,"2")) return 'a';
  if(!strcmp(str,"22")) return 'b';
  if(!strcmp(str,"222")) return 'c';
  if(!strcmp(str,"3")) return 'd';
  if(!strcmp(str,"33")) return 'e';
  if(!strcmp(str,"333")) return 'f';
  if(!strcmp(str,"4")) return 'g';
  if(!strcmp(str,"44")) return 'h';
  if(!strcmp(str,"444")) return 'i';
  if(!strcmp(str,"5")) return 'j';
  if(!strcmp(str,"55")) return 'k';
  if(!strcmp(str,"555")) return 'l';
  if(!strcmp(str,"6")) return 'm';
  if(!strcmp(str,"66")) return 'n';
  if(!strcmp(str,"666")) return 'o';
  if(!strcmp(str,"7")) return 'p';
  if(!strcmp(str,"77")) return 'q';
  if(!strcmp(str,"777")) return 'r';
  if(!strcmp(str,"7777")) return 's';
  if(!strcmp(str,"8")) return 't';
  if(!strcmp(str,"88")) return 'u';
  if(!strcmp(str,"888")) return 'v';
  if(!strcmp(str,"9")) return 'w';
  if(!strcmp(str,"99")) return 'x';
  if(!strcmp(str,"999")) return 'y';
  if(!strcmp(str,"9999")) return 'z';
  if(!strcmp(str,"1")) return '.';
  if(!strcmp(str,"11")) return ',';
  if(!strcmp(str,"111")) return '!';
  if(!strcmp(str,"1111")) return '?';

}
