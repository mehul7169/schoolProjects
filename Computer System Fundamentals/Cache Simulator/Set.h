#ifndef _SET_H
#define _SET_H

#include <stdint.h>
#include <vector>
#include "Block.h"

class Set
{
	uint32_t index, num_blocks, mruBlockIndex, origTS;
	bool lru;
	std::vector<Block *> blocks;

public:
	//Three consutrctors for different types of cache
	Set(uint32_t tag, uint32_t index);				//direct map, num_blocks = 1
	Set(uint32_t num_blocks, bool lru);				//fully associative, does not have index since there is only one set
	Set(uint32_t index, int num_blocks, bool lru); //set-assositive
	~Set();
	/*
		Return the tag of the block in the set.
		Only called for direct mapped cache.
	*/
	uint32_t DMgetTag();
	/*
		Insert new block into the set.
		Only called for assosiative cache.
	*/
	void addBlock(Block *blk);
	/*
		return the vector that contains all the blocks.
	*/
	std::vector<Block *> getBlocks();
	/*
		return the pointer to the block specificed by the tag.
		return null if the block is unfound.
	*/
	Block *findBlock(uint32_t tag);
	/*	
		Return true if the size of the set has reached 
		num_blocks. False otherwise.
	*/
	bool isFull();
	/*	
		Called when a block is hit or a new block is added. 
		Shift time stamp if the block is not accessed, reset time stamp if accessed.
		Only execute for lru assosiative cache.
	*/
	void updateTimeStamp(uint32_t accessedTag);
	/*
		Evict a block within the set and add the newBlock into the set.
		According to lru/fifo, Reorder the vector or update time stamp.
		return true if the evicted block is dirty.
	*/
	bool evict(Block *newBlock);
	/*
		Mark the block that matches the tag value dirty.
	*/
	void markDirty(uint32_t tag);
	/* 
		Checks if the specific block is dirty or not.
	*/
	bool isDirty(uint32_t tag);
};

#endif