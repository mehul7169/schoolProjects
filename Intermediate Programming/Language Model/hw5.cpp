//Mehul Agarwal
//magarw13
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
#include <sstream>
#include "language_model.h"

int main (int args, char * argv[]) {
  using std::string;
  using std::cout;
  using std::vector;
  using std::map; 
  if (args < 2) {
	fprintf(stderr, "%s\n", "Not enough arguments");
    return 1;
  }
  string operation = argv[2];
  string input = argv[1];
  vector<string> filenames = filenameRead(input);
  vector<string> words = openFiles(filenames);
  map<string, int> wordMap = createMap(words);

  if (operation == "a") {
  	if (args !=  3) {
  		fprintf(stderr, "%s\n", "Invalid number of arguments");
  	} 
  	else {
  		executeA(wordMap);
  	}
  }
  else if (operation == "d") {
  	if (args != 3) {
  		fprintf(stderr, "%s\n", "Invalid number of arguments");
  	} 
  	else {
  		executeD(wordMap);
  	}
  }

  else if (operation == "c") {
  	if (args != 3) {
  		fprintf(stderr, "%s\n", "Invalid number of arguments");
  	} 
  	else {
  		executeC(wordMap);
  	}
  }
  else if (operation == "f") {
  	string word1 = argv[3];
  	string word2 = argv[4];
  	if (args != 5) {
  		fprintf(stderr, "%s\n", "Invalid number of arguments");
  	} 
  	
  	else {
  		executeF(words, word1, word2);
  	}
  }
  else {
  	fprintf(stderr, "%s\n", "Invalid command: valid options are a, d, c, and f");
  }

}

