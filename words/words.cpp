#include<iostream>
#include<cstring>
#include<cctype>
#include"words.h"
using namespace std;

void reverse(const char* str1, char* str2){
  //copy string backwards
  int size = strlen(str1);
  for (int i = size-1; i >= 0; i--)
    str2[size-i-1]= str1[i];
  str2[size] = '\0';
}

bool compare(const char* one, const char* two){
  while (!isalpha(*one) && *one != '\0' ){one ++;}
  while (!isalpha(*two) && *two != '\0' ) {two++;}

  /*Note that : been debuged
    need to return true if both string came to end
    while(..) condition need to make sure not coming to end of the string
   */
  if (*one == '\0' && *two == '\0') return true;
  return (toupper(*one) == toupper(*two) && compare(one+1,two+1));
}

void ignore(const char* one, char* two){
  int count = 0;
  for (int i = 0; one[i]; i++){
    if (isalpha(one[i])) {
      two[count] =toupper(one[i]);
	count++;
    }
  }
    two[count] = '\0';
}
bool palindrome(const char* sentence){
  char sentence2 [80];
  ignore(sentence,sentence2);
    bool flag = true;
    int size = strlen(sentence2);
    for (int i = 0; i < size/2; i++){
      if (sentence2[i] != sentence2[size-1-i])  flag = false;
    }
    return flag;
}

/*algorithm:
First ignore the characters which we dont need
then by sort the two string from smallest to largest
if the two sorted string are the same then if should be reordered
 */

/*
Note: Debug
for function(const char*, char*)
to pass in the function paramter char*, there should have char[80] already
 */
bool anagram(const char* str1, const char* str2){
  char one[80];
  char two[80];
  //ignore the lower and upper case and characters which are not letters
   ignore(str1,one);
   ignore(str2,two);
   
   if (strlen(one) != strlen(two))
     return false;
  
   sort(one);
   sort(two);
   if (strcmp(one,two) == 0) return true;
   
  return false;
}

void sort(char* one){
  //int size = strlen(one);
  //find the smallest
  for (int i = 0; one[i]; i++){
    for (int j = i+1; one[j] ; j++){
      if (one[i] > one[j])
	{
	  char temp = one[i];
	  one[i] = one[j];
	  one[j] = temp;
	}
    }
  }
}
