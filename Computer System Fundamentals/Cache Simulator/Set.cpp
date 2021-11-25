#include "Set.h"
#include "Block.h"
#include <stdint.h>
#include <vector>
#include <iostream>

using std::vector;

//constructor for direct mapping
Set::Set(uint32_t tag, uint32_t index) : index(index)
{
	num_blocks = 1;
	lru = true;
	mruBlockIndex = 0;
	origTS = 0;
	blocks.push_back(new Block(tag));
}

//constructor for fully associative
Set::Set(uint32_t num_blocks, bool lru) : num_blocks(num_blocks), lru(lru)
{
	index = 0;
	mruBlockIndex = 0;
	origTS = 1 << (num_blocks - 2);
}

//constructor for set assosiative
Set::Set(uint32_t index, int num_blocks, bool lru) : index(index), num_blocks(num_blocks), lru(lru)
{
	mruBlockIndex = 0;
	origTS = 1 << (num_blocks - 2);
}

Set::~Set()
{
	for (uint32_t i = 0; i < blocks.size(); i++)
	{
		delete blocks[i]; //free Block objects
	}
}

uint32_t Set::DMgetTag()
{
	return blocks[0]->getTag(); //only one block per set
}

void Set::addBlock(Block *blk)
{
	blocks.push_back(blk);
}

std::vector<Block *> Set::getBlocks()
{
	return blocks;
}

Block *Set::findBlock(uint32_t tag)
{
	for (int i = 0; i < (int)blocks.size(); i++)
	{
		if (blocks[i]->getTag() == tag)
		{
			return blocks[i];
			break;
		}
	}
	return 0; //block unfound
}

bool Set::isFull()
{
	return (uint32_t)blocks.size() == num_blocks;
}

void Set::updateTimeStamp(uint32_t accessedTag)
{
	if (lru)
	{ //only lru need to update time stamp
		if (accessedTag != mruBlockIndex)
		{ //do not update ts if the mru block is used again
			for (int i = 0; i < (int)blocks.size(); i++)
			{
				if (blocks[i]->getTag() == accessedTag)
				{ //reset the used block
					blocks[i]->resetTS(origTS);
					mruBlockIndex = i; //update mru block
				}
				else
				{ //shift ts for rest of the blocks
					blocks[i]->shiftTS();
				}
			}
		}
	}
}

bool Set::evict(Block *newBlk)
{
	bool dirty = false;
	//evict block according to lru/fifo
	if (lru)
	{
		for (int i = 0; i < (int)blocks.size(); i++)
		{
			if (blocks[i]->getTS() == 0)
			{ //found oldest block
				dirty = blocks[i]->isDirty();
				delete blocks[i];
				blocks.erase(blocks.begin() + i);
				break;
			}
		}
	}
	else
	{ //vector is a queue
		dirty = blocks[0]->isDirty();
		delete blocks[0];
		blocks.erase(blocks.begin());
	}
	blocks.push_back(newBlk); //add newblock as replacement
	return dirty;
}

void Set::markDirty(uint32_t tag)
{
	for (int i = 0; i < (int)blocks.size(); i++)
	{
		if (blocks[i]->getTag() == tag)
		{
			blocks[i]->markDirty();
		}
	}
}

bool Set::isDirty(uint32_t tag)
{
	for (int i = 0; i < (int)blocks.size(); i++)
	{
		if (blocks[i]->getTag() == tag)
		{
			return blocks[i]->isDirty();
		}
	}
	return false; // return a default value here in case none of the blocks matched the tag.
}