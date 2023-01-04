#ifndef PIGLATIN_H
#define PIGLATIN_H
#include<iostream>
#include<fstream>
using namespace std;
int findFirstVowel(const char* word);

void translateWord(const char* english, char* piglatin);

void translateStream(ifstream& in, ostream& out);

#endif
