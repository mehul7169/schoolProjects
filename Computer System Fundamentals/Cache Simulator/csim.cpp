#include <iostream> // std::cout
#include <string>   // std::string, std::stoi
#include <fstream>
#include "Cache.h"
#include <math.h>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::stol;
using std::string;

int getErrorCode(int argc, int setNum, int blockNum, int blockSize, string thirdArg, string fourthArg, int writeAllocate, int writeThrough, string seventhArg);
int checkStringParams(string thirdArg, string fourthArg, int writeAllocate, int writeThrough, string seventhArg);
Cache *determineCache(int setNum, int blockNum, int blockSize, int writeAllocate, int writeThrough, bool lru);
void runCache(Cache *cache);

int main(int argc, char *argv[])
{
  //parse command line argument
  int setNum = stoi(argv[1], nullptr, 10);
  int blockNum = stoi(argv[2], nullptr, 10);
  int blockSize = stoi(argv[3], nullptr, 10);
  string thirdArg = argv[4];
  string fourthArg = argv[5];
  string seventhArg = argv[6];
  int writeAllocate = !thirdArg.compare("write-allocate") ? 1 : 0;
  int writeThrough = !fourthArg.compare("write-back") ? 0 : 1;
  bool lru = !seventhArg.compare("lru") ? true : false;
  //check if arguments are valid
  int errorCode = getErrorCode(argc, setNum, blockNum, blockSize, thirdArg, fourthArg, writeAllocate, writeThrough, seventhArg);
  if (errorCode != -1)
  {
    return errorCode;
  }
  //choose cache type and process input lines
  Cache *cache = determineCache(setNum, blockNum, blockSize, writeAllocate, writeThrough, lru);
  runCache(cache);
  cache->print();
  delete cache;
  return 0;
}

// Checks all input parameters for errors.
int getErrorCode(int argc, int setNum, int blockNum, int blockSize, string thirdArg, string fourthArg, int writeAllocate, int writeThrough, string seventhArg)
{
  if (argc != 7)
  {
    cerr << "Invalid argument amount!" << endl;
    return 1;
  }

  if (setNum < 1 || blockNum < 1 || blockSize < 4)
  {
    cerr << "All cache size parameters need to be greater than 0!" << endl;
    return 6;
  }

  bool setPower = (ceil(log2(setNum)) == floor(log2(setNum)));
  bool blockNumPower = (ceil(log2(blockNum)) == floor(log2(blockNum)));
  bool blockSizePower = (ceil(log2(blockSize)) == floor(log2(blockSize)));

  if (!setPower || !blockNumPower || !blockSizePower)
  {
    cerr << "All cache size parameters need to be a power of 2!" << endl;
    return 7;
  }

  int out = checkStringParams(thirdArg, fourthArg, writeAllocate, writeThrough, seventhArg);
  if (out != -1)
  {
    return out;
  }

  return -1;
}

// Checks string input arguments for errors.
int checkStringParams(string thirdArg, string fourthArg, int writeAllocate, int writeThrough, string seventhArg)
{
  if (thirdArg.compare("no-write-allocate") && thirdArg.compare("write-allocate"))
  {
    cerr << "Please input 'write-allocate' or 'no-write-allocate'" << endl;
    return 2;
  }
  if (fourthArg.compare("write-through") && fourthArg.compare("write-back"))
  {
    cerr << "Please input 'write-back' or 'write-through'" << endl;
    return 3;
  }
  if (!writeAllocate && !writeThrough)
  {
    cerr << "Invalid 'no-write-allocate' and 'write-back.'" << endl;
    return 4;
  }
  if (seventhArg.compare("fifo") && seventhArg.compare("lru"))
  {
    cerr << "Please put in either 'lru' or 'fifo'" << endl;
    return 5;
  }
  return -1;
}

// Determines which cache to use.
Cache *determineCache(int setNum, int blockNum, int blockSize, int writeAllocate, int writeThrough, bool lru)
{
  if (setNum >= 1 && blockNum == 1)
  {
    // Direct-mapped
    return new DMCache(setNum, blockSize, writeAllocate, writeThrough);
  }
  else if (setNum > 1 && blockNum > 1)
  {
    // BlockNum-way set-associative
    return new SACache(blockNum, setNum, blockSize, writeAllocate, writeThrough, lru);
  }
  else if (setNum == 1 && blockNum > 1)
  {
    // Fully-associative
    return new FSCache(blockNum, blockSize, writeAllocate, writeThrough, lru);
  }
  return NULL;
}

// Runs trace file with cache.
void runCache(Cache *cache)
{
  // Parse input file and update cache
  string line;
  while (getline(cin, line))
  {
    int load = line.at(0) == 'l' ? 1 : 0;
    string memStr = line.substr(2, 10); // Hex value
    // Converts memory string to uint32_t
    uint32_t mem = stoul(memStr, nullptr, 0);

    // load or store
    if (load)
    {
      cache->load(mem);
    }
    else
    {
      cache->store(mem);
    }
  }
}