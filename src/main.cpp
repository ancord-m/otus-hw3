#include <iostream>
#include <map>
#include "map_allocator.h"

int main(int argc, char *argv[])
{

	auto m = 
		std::map<int, int, std::less<int>, MapAllocator<std::pair<const int, int>>>
			{  MapAllocator<std::pair<const int, int>> {10} };

	m.insert(std::pair<const int, int>{2, 3});
	m.insert(std::pair<const int, int>{4, 6});
	m.insert(std::pair<const int, int>{5, 7});

	return 0;
}