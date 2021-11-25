# README

### Team Member

Qinyuan Wu qwu29
Matthew Liu mliu78

###Individual Responsibilities###
Qinyuan: Design and Implement Cache, Set, Block classes.
Matthew: Parse command line arguments and Implement main and Makefile. Create and run tests for different cache configurations.

###Best Cache Configuration###

////The results shown didn't differentiate between write-through/write-back, and write-allocate/no-write-allocate as they all had similar cycle trends(where to put this???).

////change size
Direct Mapped Cache(DM) was instantiated with 256 sets, 1 block, and 16 bytes per block.
Set Associative Cache(SA) was instantiated with 256 sets, 4 blocks, and 16 bytes per block.
Fully Associative Cache(FA) was instantiated with 1 set, 4 blocks, and 16 bytes per block.
Test results can be found below (the ones recorded are write-back/write-through with fifo/lru):
https://docs.google.com/spreadsheets/d/1bz9gx7OGXJkUheuzV2ixU7JbRdTjS7i9YSsVpD9918U/edit#gid=0

Write-allocated VS No-write-allocate
////Tests done between write-allocate and no-write-allocate had the same trends(in terms of ???) between caches.

Write-back VS Write-through
Write-through is much more costly in terms of write cycles, since data is stored to memory(costly) on every write hit. However, data is always stored to the cache for write-back until eviction, which greatly reduced write cycles if there are many store hits to the same address. This can be seen in comparing write-back and write-through data for write01.trace and write02.trace.

lru VS fifo
The data used were gcc.trace and swim.trace, as small amounts of data have identical performance (probably since the sets don't get filled).

////haven't carefully look through this part yet
lru:
Hit count were pretty similar among all 3 caches, which makes sense, as hits are relatively inexpensive, so there wouldn't be much variation.
For misses, the directly mapped cache was much more inefficient than the set-associative and fully associative cache for load misses.
This makes sense, as the fully associative cache allows us to place a memory block in any of the cache blocks, and thus, will fill it to capacity before having to evict, and thus, we see so little load misses. Direct-mapped caches, on the other hand determines storing data in cache based on index as it only has 1 block for the 256 sets. Thus, it is more likely to hit, resulting in a costly memory-storying operation

In total, fully associative cache had the least amount of cycles, which makes sense as it ran through a lot less misses, and thus saved many cycles for processing eviction on hit.

Thus for lru, fully-associative cache seems to be optimal.

fifo:
Fully Associative cache had a lot less load hits and a lot more misses, which attributed to it being the most inefficient.
As write-back/write-through and write-allocate/no-write-allocate had similar trends, as can be seen in the spreadsheet, the only issue seems to be the eviction method.

LRU is probably more efficient for fully-associative, as everything is stored in one set, and thus eviction happens constantly once the set is full. If you evict by least recently used, you're unlikely to access it again, and thus would result in more hits as the ones that are hit more frequently remain.

FIFO just evicts by whichever data was last first put in. Thus, highly loaded ones may be still be evicted if they were put earlier, thus causing the cache to evict and replace more often if one is constantly accessing a piece of data.

Direct-mapped caches don't have this issue, as they don't use any eviction method.

However, set-associative has the least overall cycles. It doesn't have as bad of an issue as fully-associative on eviction, as the data is relatively spread out as it has multiple sets, so eviction doesn't happen as frequently. Additionally, it has the positives of fully-associative in having a lot of space in each set, allowing for less misses.

Thus for fifo, set-associative seems optimal as shown by the data, as it has a good blend of the positives of fully-associative and direct-mapping without too much of their negatives.
