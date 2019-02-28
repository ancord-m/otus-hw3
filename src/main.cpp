#include <iostream>
#include <map>
#include "map_allocator.h"

int main(int argc, char *argv[])
{
	auto m = std::map<int, int, std::less<int>, MapAllocator<std::pair<const int, int>>>{};

	m.insert(std::pair<const int, int>{2, 3});

	return 0;
}