#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include "stamp.h"
#include<algorithm>
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char *text, char *digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
int leading_zeros(const char* digest){
  //check it is valid for hexadecimal
  for (int i = 0; digest[i]; i++){
    char ch = digest[i];
    if ( isdigit(ch)){
      if (ch > '9' || ch < '0') return -1;
    }
    if(isalpha(ch)){
      if (ch > 'f' || ch < 'a') return -1;
    }
  }
    //check how many zeros;
    int count = 0;
    bool zero = true;
    for (int i = 0; digest[i]; i++){
      if (zero && digest[i] == '0'){
	zero = true;
	count++;
      } else{
	zero = false;
      }
    }

  return count;
}

/*
Debug here: dont forget to close the file
make temp big enough since message3 is very long
while(in.eof()) gives one more postion
*/
bool file_to_SHA1_digest(const char* filename, char* digest){
  ifstream in(filename);
  if (in.fail()){
    strcpy(digest,"error");
    return false;
  }
  string s;
  //char temp[100000];
  char ch ;
  //strcpy(temp,"");
  while(in.get(ch)&& !in.eof()){
    s += ch;
    //temp[i] = ch;
    //strcat(temp,"ch");
    //i++;
  }
  
  //temp[i-1] = '\0';
  //cout << temp << endl;
  
  //cout << s << endl;
  text_to_SHA1_digest(s.c_str(),digest);
  in.close();
  return true;

}
/*
Debug here: when changing count, have to remove the last count and add new count;
More elegant way: use s+to_string(count) to put in the test_to_degist function
2)When deal with string changing here, better use string instead of c_string
*/
bool make_header(const char* recipient, const char* filename, char* header){
  strcpy(header, "");
   string s;
   s = (string)recipient;
   s += ':';
  
   ifstream in(filename);
   if (in.fail()){
     cout << "can not open the file" << endl;
     return false;
   }
   char temp[80],digest[80];
   file_to_SHA1_digest(filename,temp);
   s +=(string)temp;
   s += ':';
   int count = 0;
   string header1 = s;
   header1 += to_string(count);
   
   text_to_SHA1_digest(header1.c_str(),digest);
   
   
   while(leading_zeros(digest) < 5){
    //add count to header
     //remove the last element and add new element
     count++;
     header1 = s;
     header1 += to_string(count);
    
    text_to_SHA1_digest(header1.c_str(),digest);
  }
   
  strcpy(header,header1.c_str());
  
  return true;
}

/*
Note that: 2 ways to seperate a string, one is strtok, one is string
*/
/*
MessageStatus check_header(const char* email_address,const char* header, const char* filename){
  string hdr = header;
  //check for invalid header, header is corrrect format, two ':'
  if (count(hdr.begin(),hdr.end(),':') != 2) {
    return INVALID_HEADER;
  }
  
  //CHECK IF RECIPIENT MATCHES
  string header_email;
  header_email = hdr.substr(0,hdr.find(':'));
  if (header_email != (string)email_address) return WRONG_RECIPIENT;

  //check digest of message body matches
  char mess_digest[80];
  string given_digest;
  cout << "header is " << hdr << endl;
  given_digest = hdr.substr(hdr.find(':')+1,40); //40 is the length of the digest
 
  file_to_SHA1_digest(filename,mess_digest);
  if (strcmp(mess_digest, given_digest.c_str())!= 0) {
    return INVALID_MESSAGE_DIGEST;
  }
  //check for header digest
  char header1[80];
  make_header(email_address,filename,header1);
  if (strcmp(header1,header) != 0){
    return INVALID_HEADER_DIGEST;
  }

  
  return VALID_EMAIL;
  
}
*/

//another way, using strtok
/*
Debug here: strtok(char*, "dem");
first input should be char* instad of const char*, second input is "." instead of '.'
 */
MessageStatus check_header(const char* email_address,const char* header, const char* filename){
  char hdr[80];
  string hdr1 = header;
  strcpy(hdr,header);
 
  //check for invalid header, header is corrrect format, two ':'
  if (count(hdr1.begin(),hdr1.end(),':') != 2) {
    return INVALID_HEADER;
  }
  
  char* token = strtok(hdr, ":"); //token points to string from begining of header to ':', this position will become NULL pointer
  //CHECK IF RECIPIENT MATCHES
  char received_email[80];
  strcpy(received_email,token);
 
  if (strcmp(received_email,email_address) !=0) return WRONG_RECIPIENT;

  //check digest of message body matches
  char mess_digest[80];
  char given_digest[80];
  token = strtok(NULL, ":");
  strcpy(given_digest,token);
  file_to_SHA1_digest(filename,mess_digest);
  if (strcmp(mess_digest, given_digest)!= 0) {
    return INVALID_MESSAGE_DIGEST;
  }
  
  //check for header digest
  char header1[80];
  make_header(email_address,filename,header1);
  if (strcmp(header1,header) != 0){
    return INVALID_HEADER_DIGEST;
  }

  
  return VALID_EMAIL;
  

}

