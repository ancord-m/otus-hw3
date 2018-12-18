#ifndef MAP_ALLOCATOR_H
#define MAP_ALLOCATOR_H

#include <cstddef>

template <typename T>
struct MapAllocator
{
	using value_type = T;

	T* allocate(std::size_t n);

	template<typename U, typename... Args>
	void construct(U* p, Args&&... args);

	void destroy(T* p);

	void deallocate(T* p, std::size_t n);
};

#endif