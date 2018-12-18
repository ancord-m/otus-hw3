#include <iostream>
#include <vector>
#include "map_allocator.h"

int main(int argc, char *argv[])
{
	auto v = std::vector<int, MapAllocator<int>>{};

	return 0;
}