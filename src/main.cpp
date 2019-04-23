#include <iostream>
#include <map>
#include <vector>
#include "map_allocator.h"
#include "list.h"

#define MAX_ELEMENTS 10

//что значит расширяемость аллокатора?
//что такое совместимость с stl контейнерами?

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
void fillMap(Map &m)
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

int main(int argc, char *argv[])
{
	/*auto std_alloc_map = std::map<int, int> {};

	fillMap(std_alloc_map);


	auto own_alloc_map = 
		std::map<int, int, std::less<int>, MapAllocator<std::pair<const int, int>>>
			{  MapAllocator<std::pair<const int, int>> {MAX_ELEMENTS} };
	
	fillMap(own_alloc_map);


	printMap(std_alloc_map);
	printMap(own_alloc_map);*/

	List<int, MapAllocator<int>> l( MapAllocator<int> { 10 });
	//List<int, MapAllocator<int> > l ( MapAllocator<int> { 10 } );

	// l.push();

	return 0;
}
