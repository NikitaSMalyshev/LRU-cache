/*****************
 * Least Recently Used
 * The oldest region (least recently used) is substituted if the given region is not found
 *
 * find(10) -> 10 -1 -1 -1 -1
 * find(11) -> 10 11 -1 -1 -1
 * find(12) -> 10 11 12 -1 -1
 * find(13) -> 10 11 12 13 -1
 * find(14) -> 10 11 12 13 14
 * 
 * find(10) -> 10 11 12 13 14
 * 
 * find(50) -> 10 50 12 13 14
*/

typedef struct MemoryRegion
{
    
} MemoryRegion;

MemoryRegion regions[5];

MemoryRegion *find(int memory_region_id)
{
    
}

int main()
{

}
