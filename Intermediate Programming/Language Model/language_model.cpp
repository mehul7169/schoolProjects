//Mehul Agarwal
//magarw13

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include "language_model.h"

using namespace std;
using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::pair;

bool sortByVal(const pair<string, int> &a, const pair<string, int> &b) { 
    if (a.second > b.second) {
    	return true;
    } 
    else if (a.second == b.second) {
    	if (a.first < b.first) {
    		return true;
    	}
    	else {
    		return false;
    	}
    }
    else {
    	return false;
    }
}

std::vector<std::string> filenameRead(std::string input) {
 	ifstream fp;
 	fp.open(input);
 	if (!fp) {
 		std::cerr << "Invalid file: " << input << endl;
 		exit(1);
 	}
 	std::string x;
	using std::vector;
	using std::string;
	vector<string> filenames;
	while(fp >> x) {
		filenames.push_back(x);
	}
	fp.close();
	return filenames;
}

std::vector<std::string> openFiles(std::vector<std::string> filenames) {
	vector<string> words;
	for(vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
		ifstream fp;
		fp.open(*it);
		if (!fp) {
 			std::cerr << "Invalid file: " << *it << endl;
 		}
		string x;
		words.push_back("<START_1>");
		words.push_back("<START_2>");
		
		while(fp >> x) {
			words.push_back(x);
		}
		words.push_back("<END_1>");
		words.push_back("<END_2>");
		fp.close();
	}
	return words;
}

std::map<std::string, int> createMap(std::vector<std::string> words) {
	map<string, int> wordMap;
	string trigram;
	for(vector<string>::iterator it = words.begin(); it != words.end() - 2; ++it) {
		if (*it == "<END_1>") {
			it+=2;
		}
  		trigram = "[" + *it + " " + *(it + 1) + " " + *(it + 2)+ "]" ;
  		if (wordMap.find(trigram) != wordMap.end()) {
  			wordMap[trigram] = wordMap[trigram] + 1;
  		}
  		else {
  			wordMap[trigram] = 1;
  		}
    }
    return wordMap;
}

void executeA(std::map<std::string, int> wordMap) {
	for(map<string, int>::iterator it = wordMap.begin();
		it != wordMap.end();
		++it) {
		cout << it->second << " -"<< " " << it->first << std::endl;
	}
}

void executeD(std::map<std::string, int> wordMap) {
  	for(map<string, int>::reverse_iterator it = wordMap.rbegin();
		it != wordMap.rend();
		++it) {
		cout << it->second << " -"<< " " << it->first << std::endl;
	}
	// cout << wordMap.front();
}

void executeC(std::map<std::string, int> wordMap) {
	vector<pair<string, int>> wordMapVector;
	for(map<string, int>::iterator it = wordMap.begin();
		it != wordMap.end();
		++it) {
		wordMapVector.push_back(make_pair(it->first, it->second));
	}
	sort(wordMapVector.begin(), wordMapVector.end(), sortByVal);
	for (int i = 0; i < (int) wordMapVector.size(); i++)
	{
		cout << wordMapVector[i].second << " -"<< " " << wordMapVector[i].first << std::endl;
	}
}

void executeF(std::vector<std::string> words, std::string word1, std::string word2) {
	string trigram;
	map<string, int> Map;
	for (int i = 0; i < (int) words.size(); i++) {
		if (words[i] == word1 && words[i + 1] == word2) {
			trigram = "[" + word1 + " " + word2 + " " + words[i + 2] + "]";	
			if (Map.find(trigram) != Map.end()) {
  			Map[trigram] = Map[trigram] + 1;
  			}
  			else {
  				Map[trigram] = 1;
			}	
		}
	}
	vector<pair<string, int>> wordMapVector;
	for(map<string, int>::iterator it = Map.begin();
		it != Map.end();
		++it) {
		wordMapVector.push_back(make_pair(it->first, it->second));
	}
	sort(wordMapVector.begin(), wordMapVector.end(), sortByVal);
	if (wordMapVector.size() == 0) {
		cout << "No trigrams of the form [x y ?] appear";
	}
	else {
		cout << wordMapVector[0].second << " -"<< " " << wordMapVector[0].first << std::endl;
	}


}



