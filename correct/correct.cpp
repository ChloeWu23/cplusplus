#include <iostream>
#include<cstring>
#include<cctype>
#include"correct.h"
using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */
/*
void text_to_binary(const char* str, char* binary){
  strcpy(binary,"");
  for (int i = 0; str[i];i++){
    char temp[80];
    ascii_to_binary(str[i],temp);
    strcat(binary,temp);
  }
}
*/
//recursive way
void text_to_binary(const char* str, char* binary){
  if(strlen(str)){
    //char temp[80];
    ascii_to_binary(*str,binary);
    text_to_binary(str+1,binary+8);
  }
  return;
}
/*
void binary_to_text(const char* binary, char* text){
  strcpy(text,"");
  char temp[80];
  //char ch;
  int count = 0;
  int i = 0;
  while(binary[i]){
    for(int j =0; j < 8; j++){
      temp[j]= binary[i+j];
    }
    temp[8]='\0';
    text[count]=binary_to_ascii(temp);
    count++;
    i = i+8;
  }
  text[count] = '\0';
}
*/
/*recursive way*/
void binary_to_text(const char* binary, char* text){
  if(strlen(binary)){
    char temp[80];
    strncpy(temp,binary,8);
    temp[8] = '\0';
    *text=binary_to_ascii(temp);
      binary_to_text(binary+8,text+1);
    }
  else{
    *(text) = '\0';
  }
}
void add_error_correction(const char* data, char* corrected){
  int size = strlen(data);
  char temp[80];
  strcpy(corrected,"");
  for (int i = 0; i < size/4; i++){
    //fill in temp the 7 digits
   char c1,c2,c3;
    int d=i*4;
    c1 = parity(data[d],data[d+1],data[d+3]);
    c2 = parity(data[d],data[d+2],data[d+3]);
    c3 = parity(data[d+1],data[d+2],data[d+3]);
    temp[0] = c1;
    //cout << "c1 is "<< c1 << endl;
    temp[1] = c2;
    temp[2]=data[d];
    temp[3] =c3;
    temp[4]=data[d+1];
    temp[5]=data[d+2];
    temp[6]=data[d+3];
    temp[8] = '\0';
    // cout << "hello" <<temp << endl;
    strcat(corrected,temp);
  }

}

char parity(char c1, char c2, char c3){
  int num;
  num = (c1- '0') + (c2 - '0') + (c3 - '0');
  //if even
  if (num /2 || num ==0) return '0';
  else return '1';

}

char parity(char c1, char c2, char c3,char c4){
  int num;
  num = (c1- '0') + (c2 - '0') + (c3 - '0')+(c4 -'0');
  
  if (num %2 ) return '1';
  else return '0';

}

/* Algorithm:
did it in a recursive way
*/
int decode(const char* recieved, char* decoded){
  int error = 0;
  strcpy(decoded,"");
  int size = strlen(recieved); // to see how mant times of 7
  char p1,p2,p3;
  char b[80];
  for (int i =0; i< size/7;i++){
    int d=i/7;
    for(int j = 0; j < 7; j++)
      b[j]=recieved[d+j];
    
    b[7] = '\0';
    // cout << b << endl;
    p1 = parity(b[3],b[4],b[5],b[6]);
    p2 = parity(b[1],b[2],b[5],b[6]);
    p3 = parity(b[0],b[2],b[4],b[6]);
    // cout << p1 << p2 << p3 << endl;
  //has error
   error=(p1-'0')+(p2-'0')+(p3-'0');
  if (error>0){
    int num= (p3-'0')+2 *(p2-'0')+4*(p1-'0')-1;
    //cout << "num is "<<num << endl;
    b[num] = (b[num] == '0')? '1': '0';
    //cout << "b is " << b << endl;
  }
  
  //copy characters
  char temp[80];
  temp[0]=b[2];
  temp[1]=b[4];
  temp[2]=b[5];
  temp[3]=b[6];
  temp[4]= '\0';
  strcat(decoded,temp);
  }
  
  return error;
	  }
    
