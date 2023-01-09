#ifndef MULTITAP_H
#define MULTITAP_H
//#include<iostream>
using namespace std;
int encode_character(char ch, char* multitap);

void encode(const char* plaintext, char* multitap);

void decode(ifstream& in, ostream& out);
char decode(char* str);
#endif
