#include <iostream>
#include <map>
#include "map_allocator.h"




int main(int argc, char *argv[])
{
	auto m = std::map<int, int, MapAllocator<int>>{};

	m.insert( std::pair<int, int>{2, 3});

	return 0;
}