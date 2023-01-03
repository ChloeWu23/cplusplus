#ifndef SOUNDEX_H
#define SOUNDEX_H

void encode(const char* surname, char* soundex);
bool compare(const char* first, const char* second);
char code(char letter);
int count(const char* surname, const char* sentence);
#endif
