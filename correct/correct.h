#ifndef CORRECT_H
#define CORRECT_H
#include<cstring>
void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char *binary);
void text_to_binary(const char* str, char* binary);
void binary_to_text(const char* binary, char* text);
void add_error_correction(const char* data, char* correct);
//char parity(char d1,char d2, char d3);
char parity(char c1,char c2, char c3, char c4 = '0');

int decode(const char* recieved, char* decode);
#endif
