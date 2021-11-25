//Mehul Agarwal
//magarw13

#ifndef LANGUAGE_MODEL_H
#define LANGUAGE_MODEL_H

#include <cstdio>

std::vector<std::string> filenameRead(std::string input);

std::vector<std::string> openFiles(std::vector<std::string> filenames);

std::map<std::string, int> createMap(std::vector<std::string> words);


void executeA(std::map<std::string, int> wordMap);

void executeD(std::map<std::string, int> wordMap);

void executeC(std::map<std::string, int> wordMap);

void executeF(std::vector<std::string> words, std::string word1, std::string word2);


#endif