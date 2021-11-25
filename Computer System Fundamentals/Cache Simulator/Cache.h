#ifndef _CACHE_H
#define _CACHE_H

#include <stdint.h>
#include <map>
#include "Set.h"

/*
	An abstract base class of cache.
	Implements the print method.
*/
class Cache
{
protected:
	int cycles, sMiss, sHit, lMiss, lHit, numBlocks, numSets, blockSize;
	bool writeThrough, writeAllocate, lru; //if lri = 0, fifo, writeThrough/writeBack
public:
	Cache(int n_set, int n_blocks, int block_size, int wAll, int wThr);
	void print(); //print summary of hit/miss/cycle
	virtual ~Cache();
	virtual void load(uint32_t adr) = 0; //load address into cache
	virtual void store(uint32_t adr) = 0; //write address into cache
};

/*
	Direct-mapped cache.
	Has one or more sets that each contains one block.
	A map is used to store the index and its associated set.
	A new set is added to the map when an index is requested by the input address for the first time.
*/
class DMCache : public Cache
{
	std::map<uint32_t, Set *> indexToSet; //a map that stores the index as key and the set object as value
	int num_TagBits, num_IndexBits, num_OffsetBits;

public:
	DMCache(int n_sets, int block_size, int wAll, int wThr); //initialize empty cache
	void print();
	virtual ~DMCache();
	virtual void load(uint32_t adr);
	virtual void store(uint32_t adr);

private:
	void loadHit(); 
	void loadMiss(uint32_t tag, uint32_t index, bool evict); 
	void storeHit(uint32_t tag, uint32_t index);
	void storeMiss(uint32_t tag, uint32_t index, bool evict);
};

/*
	Fully associative cache.
	Has one set that has one or more blocks.
	Contains a pointer to the set object.
*/
class FSCache : public Cache
{
	int num_TagBits, num_OffsetBits, num_blocks;
	Set *set; //only one set that stores all the blocks
	bool lru;

public:
	FSCache(int n_blocks, int block_size, int wAll, int wThr, bool LRU); //initialize empty cache
	void print();
	virtual ~FSCache();
	virtual void load(uint32_t adr);
	virtual void store(uint32_t adr);

private:
	void loadHit(uint32_t tag);
	void loadMiss(uint32_t tag, bool evict);
	void storeHit(uint32_t tag);
	void storeMiss(uint32_t tag, bool evict);
};

/*
	Set associative cache.
	Has one or more sets that each contains one or more blocks.
	A map is used to store the index and its associated set.
	A new set is added to the map when an index is requested by the input address for the first time.
*/
class SACache : public Cache
{
	int num_TagBits, num_OffsetBits, num_IndexBits, num_blocks;
	std::map<uint32_t, Set *> indexToSet;
	bool lru;

public:
	SACache(int n_blocks, int n_sets, int block_size, int wAll, int wThr, bool LRU);
	void print();
	virtual ~SACache();
	virtual void load(uint32_t adr);
	virtual void store(uint32_t adr);

private:
	void loadHit(uint32_t tag, uint32_t index);
	void loadMiss(uint32_t tag, uint32_t index, bool evict, bool emptySet);
	void storeHit(uint32_t tag, uint32_t index);
	void storeMiss(uint32_t tag, uint32_t index, bool evict, bool emptySet);
};

#endif