#ifndef _BLOCK_H
#define _BLOCK_H

#include <stdint.h>

class Block
{
	uint32_t tag, ts; //ts = time stamp for lru
	bool dirty;

public:
	Block(uint32_t tag);
	Block(uint32_t tag, uint32_t timeStamp); //constructor for lru
	void assignTag(uint32_t newTag);				 //change tag value
	uint32_t getTag();											 //return tag value
	uint32_t getTS();												 //return time stamp
	void resetTS(uint32_t origValue);				 //reset time stamp when a block is accessed
	void shiftTS();													 //right shift time stamp by 1 when a block is not accessed
	void markDirty();												 //defer write to memory until replacement
	bool isDirty();													 //return dirty value
};

#endif