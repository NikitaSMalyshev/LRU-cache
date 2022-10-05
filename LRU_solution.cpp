#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
constexpr int region_count = 5;

/*****************
 * Least Recently Used
 * The least recently used memory region is recycled in case the given region is not found
 * 
 * test_vector = {10, 11, 12, 13, 14, 10, 50, 10, 12, 51}
 * 
 * also added the resulting state of LRU_positions list
 * after find(...) call
 * 
 * find(10) -> 10 -1 -1 -1 -1  |  list : 0
 * find(11) -> 10 11 -1 -1 -1  |  list : 0, 1
 * find(12) -> 10 11 12 -1 -1  |  list : 0, 1, 2
 * find(13) -> 10 11 12 13 -1  |  list : 0, 1, 2, 3
 * find(14) -> 10 11 12 13 14  |  list : 0, 1, 2, 3, 4
 * 
 * find(10) -> 10 11 12 13 14  |  list : 1, 2, 3, 4, 0
 * 
 * find(50) -> 10 50 12 13 14  |  list : 2, 3, 4, 0, 1
 * 
 * find(10) -> 10 50 12 13 14  |  list : 2, 3, 4, 1, 0
 * 
 * find(12) -> 10 50 12 13 14  | list : 3, 4, 1, 0, 2
 * 
 * find(51) -> 10 50 12 51 14  | list : 4, 1, 0, 2, 3
 * 
 * find(14) -> 10 50 12 51 14  | list : 1, 0, 2, 3, 4
 * 
 * find(52) -> 10 5 12 51 14  | list : 0, 2, 3, 4, 1
*/

// NOTE: 
// I added usage of std::list and std::find 
// to make the code less cumbersome.
// But it all can be done by hand I think if needed

struct MemoryRegion
{
    int id;
    
    // otherwise it would be initialized with 0
    MemoryRegion() {
        id = -1;
    }
};

MemoryRegion regions[region_count];

// list of positions in the regions array
// LRU position is at the front of the list
// and MRU is at the back
list<size_t> LRU_positions;

// list contains positions in the regions array
void LRU_move_value_to_back(size_t position) {
    auto iter = std::find(LRU_positions.begin(), LRU_positions.end(), position);
    if(iter != LRU_positions.end()) {
        LRU_positions.erase(iter);
    }
    LRU_positions.push_back(position);
}

// LRU find, using the same list we can do a MRU find too
MemoryRegion *find(int memory_region_id)
{
    cout << "FIND: " << memory_region_id << endl;
    
    // find the id
    for(size_t i = 0; i < region_count; i++) {
        if(regions[i].id == memory_region_id) {
            LRU_move_value_to_back(i);
            return regions + i;
        }
    }
    
    // find first unused position
    size_t i = 0;
    while(regions[i].id != -1 && i < region_count) {
        ++i;
    }
    
    // use the LRU position if no unused one
    if(i == region_count) {
        i = LRU_positions.front();
        LRU_positions.pop_front();
    } 
    
    // use position i
    regions[i].id = memory_region_id;
    LRU_positions.push_back(i);
    return regions + i;
}

void print()
{
    for(auto reg : regions)
        cout << reg.id << " ";
    cout << "\n";
}

void print_LRU_positions()
{
    for(auto pos : LRU_positions)
        cout << pos << " ";
    cout << "\n";
}

int main()
{
    int test_vector[] = {10, 11, 12, 13, 14, 10, 50, 10, 12, 51, 14, 52};
    for(auto val : test_vector)
    {
        find(val);
        cout << "REGIONS: ";
        print();
        cout << "POSITIONS: ";
        print_LRU_positions();
        cout << endl;
    }
}

