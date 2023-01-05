#ifndef PLAYFAIR_H
#define PLAYFAIR_H

void prepare(const char* input, char* output);
void grid(const char* codeword, char playfair[6][6]);
bool occurs_before(const char* str, char letter, int position);
int find_row(const char square[6][6], char ch);
int find_col(const char square[6][6], char ch);
void bigram(const char square[6][6], char char1, char char2, char &out1, char &out2);
void encode(const char square[6][6], const char* prepared, char* encoded);
void decode(const char square[6][6], const char* encoded, char* decoded);
#endif
