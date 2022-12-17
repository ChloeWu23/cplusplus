#ifndef SPELL_H
#define SPELL_H
const int Max_Length = 80;
/* insert your function declaration here */
int frequency(const char* word);

int edit_distance(const char* a, const char* b,int limit= Max_Length);

int edit_distance(const char* a, const char* b, int i, int j, int total,int limit);

bool spell_correct(const char* word, char* fixed);

int indicator(char x, char y);

int edit_distance_bonus(const char* a,const char* b);

#endif
