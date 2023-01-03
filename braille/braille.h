#ifndef BRAILLE_H
#define BRAILLE_H
#include<iostream>
using namespace std;
int encode_character(char ch, char* braille);
void code(char ch,char* temp);
void encode(const char* plaintext,char* braille);
void print_braille(const char* plaintext, ostream& output);
#endif
