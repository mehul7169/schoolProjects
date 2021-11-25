#include "Cache.h"
#include <stdint.h>
#include <map>
#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::endl;
using std::map;
using std::string;

void parseAdr(uint32_t adr, uint32_t &index, uint32_t &tag, uint32_t num_OffsetBits, uint32_t num_IndexBits);

//Cache constructor
Cache::Cache(int n_set, int n_blocks, int block_size, int wAll, int wThr) : numBlocks(n_blocks), numSets(n_set), blockSize(block_size), writeThrough(wThr), writeAllocate(wAll)
{
	cycles = 0;
	sMiss = 0;
	sHit = 0;
	lMiss = 0;
	lHit = 0;
}

Cache::~Cache() {}

void Cache::print()
{
	cout << "Total loads: " << lMiss + lHit << endl;
	cout << "Total stores: " << sMiss + sHit << endl;
	cout << "Load hits: " << lHit << endl;
	cout << "Load misses: " << lMiss << endl;
	cout << "Store hits: " << sHit << endl;
	cout << "Store misses: " << sMiss << endl;
	cout << "Total cycles: " << cycles << endl;
}

/***********DMCache****************/
//calling super constructor
DMCache::DMCache(int n_sets, int block_size, int wAll, int wThr) : Cache(n_sets, 1, block_size, wAll, wThr)
{
	num_OffsetBits = log(block_size) / log(2);				 //log2(block_size)
	num_IndexBits = log(n_sets) / log(2);							 //log2(set_size)
	num_TagBits = 32 - num_IndexBits - num_OffsetBits; //the rest are all tagbits
}

DMCache::~DMCache()
{
	for (uint32_t i = 0; i < indexToSet.size(); i++)
	{
		delete indexToSet[i]; //free Set objects
	}
}

void DMCache::load(uint32_t adr)
{
	//parse adr
	uint32_t index, tag;
	parseAdr(adr, index, tag, num_OffsetBits, num_IndexBits);
	//determine hit or miss
	if (indexToSet.find(index) == indexToSet.end())
	{
		loadMiss(tag, index, false); //index is empty
	}
	else if (indexToSet[index]->DMgetTag() == tag) // compare tag of the set/block
	{
		loadHit(); //both index and tag match
	}
	else
	{
		loadMiss(tag, index, true); //replace current set
	}
}

void DMCache::loadHit() // TODO: Why do we need these parameters?
{
	lHit++;
	cycles++; //load from cache, 1 cycle only
}

void DMCache::loadMiss(uint32_t tag, uint32_t index, bool evict)
{
	lMiss++;
	cycles += blockSize / 4 * 100 + 1; //load from memory, 100 cycles per 4-byte quantity
	if (evict)
	{
		if (!writeThrough && indexToSet[index]->isDirty(tag))
		{
			cycles += blockSize / 4 * 100; //write to mem upon eviction
		}
		delete indexToSet[index];
		indexToSet.erase(indexToSet.find(index)); //erase set
	}
	indexToSet[index] = new Set(tag, index); //old block/set would be replaced
}

void DMCache::store(uint32_t adr)
{
	//parse adr
	uint32_t index, tag;
	parseAdr(adr, index, tag, num_OffsetBits, num_IndexBits);
	//determine hit or miss
	if (indexToSet.find(index) == indexToSet.end())
	{
		storeMiss(tag, index, false); //index is empty
	}
	else if (indexToSet[index]->DMgetTag() == tag)
	{
		storeHit(tag, index); //both index and tag match
	}
	else
	{
		storeMiss(tag, index, true); //replace current set
	}
}

void DMCache::storeHit(uint32_t tag, uint32_t index)
{
	sHit++;
	if (writeThrough)
	{
		cycles += blockSize / 4 * 100 + 1; //write to memory, 100 cycles per 4-byte quantity
	}
	else
	{																		 //write-back
		cycles++;													 //write to cache only
		indexToSet[index]->markDirty(tag); //mark the block dirty
	}
}

void DMCache::storeMiss(uint32_t tag, uint32_t index, bool evict)
{
	sMiss++;
	cycles += blockSize / 4 * 100 + 1;
	if (writeAllocate)
	{
		if (evict)
		{
			if (!writeThrough && indexToSet[index]->isDirty(tag))
			{
				cycles += blockSize / 4 * 100; //write to mem upon eviction
			}
			delete indexToSet[index];
			indexToSet.erase(indexToSet.find(index)); //erase set
		}
		indexToSet[index] = new Set(tag, index); //create new set
		if (!writeThrough)
		{ //write-back
			indexToSet[index]->markDirty(tag);
		}
	}
}

//parse the physical address into indexBits and tagBits
void parseAdr(uint32_t adr, uint32_t &index, uint32_t &tag, uint32_t num_OffsetBits, uint32_t num_IndexBits)
{
	adr = adr >> num_OffsetBits;
	index = adr & ((1 << num_IndexBits) - 1); //grab the lowest num_indexbits
	tag = adr >> num_IndexBits;

	//tag -= 1048576;
}

/************FSCache****************/
FSCache::FSCache(int n_blocks, int block_size, int wAll, int wThr, bool LRU) : Cache(1, n_blocks, block_size, wAll, wThr)
{
	set = new Set(n_blocks, LRU);							 //initiate set with fully associative constructor
	num_OffsetBits = log(block_size) / log(2); //log2(block_size)						 //log2(set_size)
	num_TagBits = 32 - num_OffsetBits;
	lru = LRU;
	num_blocks = n_blocks;
}

FSCache::~FSCache()
{
	delete set;
}

void FSCache::load(uint32_t adr)
{
	//parse adr
	adr = adr >> num_OffsetBits;
	uint32_t tag = adr;

	Block *blk = set->findBlock(tag);
	if (blk != 0)
	{ //block with matching tag is found
		loadHit(tag);
	}
	else
	{
		bool evict = set->isFull(); //need to evict if set if full
		loadMiss(tag, evict);
	}
}

void FSCache::loadHit(uint32_t tag)
{
	cycles++;
	lHit++;
	set->updateTimeStamp(tag); //the function will check if it is lru
}

void FSCache::loadMiss(uint32_t tag, bool evict)
{
	lMiss++;
	cycles += blockSize / 4 * 100 + 1; //load from memory, 100 cycles per 4-byte quantity
	uint32_t origTS = 1 << (num_blocks - 2);
	if (evict)
	{
		bool dirty = set->evict(new Block(tag, origTS)); //evict and add new block
		if (dirty && !writeThrough)
		{
			cycles += blockSize / 4 * 100; //write to mem upon eviction
		}
	}
	else
	{
		set->addBlock(new Block(tag, origTS));
		set->updateTimeStamp(tag);
	}
}

void FSCache::store(uint32_t adr)
{
	//parse adr
	adr = adr >> num_OffsetBits;
	uint32_t tag = adr;

	Block *blk = set->findBlock(tag);
	if (blk != 0)
	{ //block with matching tag is found
		storeHit(tag);
	}
	else
	{
		bool evict = set->isFull(); //need to evict if set if full
		storeMiss(tag, evict);
	}
}

void FSCache::storeHit(uint32_t tag)
{
	sHit++;
	if (writeThrough)
	{
		cycles += blockSize / 4 * 100 + 1;
		set->updateTimeStamp(tag);
	}
	else
	{
		cycles++;
		set->markDirty(tag); //write-back
	}
}

void FSCache::storeMiss(uint32_t tag, bool evict)
{
	sMiss++;
	cycles += blockSize / 4 * 100 + 1;
	if (writeAllocate)
	{
		uint32_t origTS = 1 << (num_blocks - 2);
		if (evict)
		{
			bool dirty = set->evict(new Block(tag, origTS));
			if (dirty && !writeThrough)
			{
				cycles += blockSize / 4 * 100; //write to mem upon eviction
			}
		}
		else
		{
			set->addBlock(new Block(tag, origTS));
			set->updateTimeStamp(tag);
		}

		//update cycles
		if (!writeThrough)
		{
			set->markDirty(tag);
		}
	}
}

/***************SACache******************/
SACache::SACache(int n_blocks, int n_sets, int block_size, int wAll, int wThr, bool LRU) : Cache(n_sets, n_blocks, block_size, wAll, wThr)
{
	lru = LRU;
	num_OffsetBits = log(block_size) / log(2);				 //log2(block_size)
	num_IndexBits = log(n_sets) / log(2);							 //log2(set_size)
	num_TagBits = 32 - num_IndexBits - num_OffsetBits; //the rest are all tagbits
	num_blocks = n_blocks;
}

SACache::~SACache()
{
	for (uint32_t i = 0; i < indexToSet.size(); i++)
	{
		delete indexToSet[i]; //free Set objects
	}
}

void SACache::load(uint32_t adr)
{
	//parse adr
	uint32_t index, tag;
	parseAdr(adr, index, tag, num_OffsetBits, num_IndexBits);
	//determine hit or miss
	if (indexToSet.find(index) == indexToSet.end())
	{
		loadMiss(tag, index, false, true); //set has not been created in the map
	}
	else if (indexToSet[index]->findBlock(tag) != 0) // compare tag of the set/block
	{
		loadHit(tag, index); //both index and tag match
	}
	else
	{ //set is created but no block matches
		bool evict = indexToSet[index]->isFull();
		loadMiss(tag, index, evict, false); //add new block or evict block if set is full
	}
}

void SACache::loadHit(uint32_t tag, uint32_t index)
{
	lHit++;
	cycles++;
	indexToSet[index]->updateTimeStamp(tag);
}

void SACache::loadMiss(uint32_t tag, uint32_t index, bool evict, bool emptySet)
{
	lMiss++;
	cycles += blockSize / 4 * 100 + 1;
	uint32_t origTS = 1 << (num_blocks - 2);
	if (evict)
	{
		bool dirty = indexToSet[index]->evict(new Block(tag, origTS));
		if (!writeThrough && dirty)
		{
			cycles += blockSize / 4 * 100; //write back, write to mem upon eviction
		}
	}
	else
	{ //set is not full
		if (emptySet)
		{ //create new set
			indexToSet[index] = new Set(index, num_blocks, lru);
		}
		indexToSet[index]->addBlock(new Block(tag, origTS));
		indexToSet[index]->updateTimeStamp(tag);
	}
}

void SACache::store(uint32_t adr)
{
	//parse adr
	uint32_t index, tag;
	parseAdr(adr, index, tag, num_OffsetBits, num_IndexBits);
	//determine hit or miss
	if (indexToSet.find(index) == indexToSet.end())
	{
		storeMiss(tag, index, false, true); //set has not been created in the map
	}
	else if (indexToSet[index]->findBlock(tag) != 0) // compare tag of the set/block
	{
		storeHit(tag, index); //both index and tag match
	}
	else
	{ //set is created but no block matches
		bool evict = indexToSet[index]->isFull();
		storeMiss(tag, index, evict, false); //add new block or evict block if set is full
	}
}

void SACache::storeHit(uint32_t tag, uint32_t index)
{
	sHit++;
	if (writeThrough)
	{
		cycles += blockSize / 4 * 100 + 1;
	}
	else
	{ //write-back
		cycles++;
		indexToSet[index]->markDirty(tag);
	}
	indexToSet[index]->updateTimeStamp(tag);
}

void SACache::storeMiss(uint32_t tag, uint32_t index, bool evict, bool emptySet)
{
	sMiss++;
	cycles += blockSize / 4 * 100 + 1;
	if (writeAllocate)
	{
		uint32_t origTS = 1 << (num_blocks - 2);
		//add new block pr replace evicted block
		if (evict)
		{
			bool dirty = indexToSet[index]->evict(new Block(tag, origTS));
			if (!writeThrough && dirty)
			{
				cycles += blockSize / 4 * 100; //write back, write to mem upon eviction
			}
		}
		else
		{
			if (emptySet)
			{
				indexToSet[index] = new Set(index, num_blocks, lru);
			}
			indexToSet[index]->addBlock(new Block(tag, origTS));
			indexToSet[index]->updateTimeStamp(tag);
		}
		//update cycles
		if (!writeThrough)
		{
			indexToSet[index]->markDirty(tag);
		}
	}
}