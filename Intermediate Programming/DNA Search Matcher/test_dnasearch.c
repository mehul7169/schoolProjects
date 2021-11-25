//Mehul Agarwal
//magarw13
#include <stdio.h>
#include "dnasearch.h"
#include <assert.h>
#include <string.h>
int main() {
  char testArray[15000];
  fgets(testArray, 15000, stdin);
  char testPattern[15000];
  fgets(testPattern, 15000, stdin);
  int strLen = 1; // input is A
  int textLen = 4; //input is ACGT
  int checkRight = pattern_check(textLen, testPattern, strLen);
  assert(checkRight == 1);
  int matchRight = pattern_match(testArray, textLen, testPattern, strLen, 0);
  assert(matchRight == 0);
  char testArray2[15000] = "ACCC";
  char testPattern2[15000] = "d";
  int checkNotRight = pattern_check(textLen, testPattern2, strLen);
  assert(checkNotRight == -1);
  char testPatter2[10] = "g";
  int matchNotRight = pattern_match(testArray2, 4, testPatter2, 1, 0);
  assert(matchNotRight == -1);
  
  
}


