#include <iostream>
#include <map>
#include <vector>

#include "map_allocator.h"
#include "list.h"

#define MAX_ELEMENTS 10

long factorial(int value)
{
	if(value < 0)
	{
		return 0;
	}

	if(value == 0)
	{
		return 1;
	}

	return value * factorial(value - 1);
}

template<typename Map>
void fillMap(Map& m)
{
	for(int i = 0; i < MAX_ELEMENTS; ++i)
	{
		m.insert(std::make_pair(i, factorial(i)));
	}
}

template<typename Map>
void printMap(Map &m)
{
	for (auto it = m.begin(); it != m.end(); ++it) 
	{
        std::cout << it->first << " " << it->second << std::endl;
    }
}

template<typename Container>
void fillContainer(Container &c)
{
	for(auto i = 0; i < MAX_ELEMENTS; ++i)
	{
		c.push(i);
	}
}

template<typename Container>
void printContainer(Container &c)
{
	for(auto elm : c)
	{
		std::cout << elm << std::endl;
	}
}

int main(int argc, char *argv[])
{
	/* map */

	auto std_alloc_map = std::map<int, int> { };

	fillMap(std_alloc_map);

	auto own_alloc_map = 
		std::map<int, int, std::less<int>, MapAllocator<std::pair<const int, int>>>
			(  MapAllocator<std::pair<const int, int>> { MAX_ELEMENTS } );

	fillMap(own_alloc_map);

	printMap(std_alloc_map);
	printMap(own_alloc_map);

	/* int container */
	
	List<int> std_alloc_list;

	fillContainer(std_alloc_list);	

	List<int, MapAllocator<int>> own_alloc_list { MapAllocator<int> { MAX_ELEMENTS } };

	fillContainer(own_alloc_list);

	printContainer(std_alloc_list);
	printContainer(own_alloc_list);	

	return 0;
}
