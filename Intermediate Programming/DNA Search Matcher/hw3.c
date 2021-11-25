//Mehul Agarwal
//magarw13
#include <stdio.h>
#include <string.h>
#include "dnasearch.h"
#include <ctype.h>
int main(int argc, char* argv[]) {
  //checks whether the input is right or not
  if (argc !=  2) {
    printf("Invalid input");
  }
  //opens input file
  FILE* input = fopen(argv[1], "r");
  //checks if the textfile opened correctly or not
  if (input == NULL) {
    printf("Error: could not open input file");
    return 1;
  }
  char array[15000];
  int size = 0;
  char a;
  //runs a while loop until input exists
  int numCollected = fscanf(input, " %c", &a);
  while (numCollected == 1){
      array[size] = a;
      //checks whether text is valid or not
      if (array[size] != 'a' && array[size] != 'A' && array[size] != 'c' && array[size] != 'C' && array[size] != 'g' && array[size] != 'G' && array[size] != 't' && array[size] != 'T') {
	printf("Invalid text\n");
	return -1;
      }
      size++;
      if (size > 15000) {
	printf("Invalid Text");
	return -1;
      }
      numCollected = fscanf(input, " %c", &a);
  }
  
  fclose(input);
  //converts all lowercase letters to uppercase letters
  for (int i  = 0; i < size; i++) {
    if (array[i] == 'a') {
      array[i] = 'A';
    }
    else if (array[i] == 'g') {
      array[i] = 'G';
    }
    else if (array[i] == 'c') {
      array[i] = 'C';
    }
    else if (array[i] == 't') {
      array[i] = 'T';
    }
  }
  //starts reading the patter
  //uses the start value to sens start_At
  // uses numPatternCollected to keep reading the patter
  //uses numPatterFound to check in the end if any pattern was found
  char pattern[15001];
  int numPatternCollected = scanf("%s", pattern);
  int start_value = 0;
  int numPatternFound = 0;
  while (numPatternCollected !=  -1) {
    //resets them for each pattern
    numPatternFound = 0;
    start_value = 0;
    //converts from lowercase to uppercase if pattern is valid
    if (pattern_check(size, pattern, strlen(pattern)) == 1) {
      for (int h = 0; h < (int)strlen(pattern); h++) {
	if (pattern[h] == 'a' || pattern[h] == 'c' || pattern[h] == 'g' || pattern[h] == 't') {
	  pattern[h] = toupper(pattern[h]);
	}
      }
      //prints the pattern each time
      fprintf(stdout, "%s", pattern);
      while (start_value <= (int)size - (int)strlen(pattern)) {
	//checks whether it matches or not
	start_value = pattern_match(array, size, pattern,(int) strlen(pattern),start_value);
	
	if (start_value != -1) {
	  //prints the index where match is found
	  fprintf(stdout, " %d", start_value);
	  numPatternFound++;
	} else {
	  break;
	}
	start_value++;
      }
    }
    //output for invalid pattern
    else {
      fprintf(stdout, "Invalid pattern\n");
      return -1;
    }
    //output if match not found
    if (numPatternFound == 0) {
      fprintf(stdout, " Not found");
    }
    //reads pattern again
    numPatternCollected = scanf("%s", pattern);
    printf("\n");
  }
  return 0;
}
  
