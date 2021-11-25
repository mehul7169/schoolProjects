#include "Block.h"
#include <stdint.h>

Block::Block(uint32_t tag) : tag(tag), ts(0), dirty(false) {}

Block::Block(uint32_t tag, uint32_t timeStamp) : tag(tag), ts(timeStamp), dirty(false) {}

void Block::assignTag(uint32_t newTag)
{
	tag = newTag;
}

uint32_t Block::getTag()
{
	return tag;
}

uint32_t Block::getTS()
{
	return ts;
}

void Block::resetTS(uint32_t origValue)
{
	ts = origValue;
}

void Block::shiftTS()
{
	ts = ts >> 1;
}

void Block::markDirty()
{
	dirty = true;
}

bool Block::isDirty()
{
	return dirty;
}