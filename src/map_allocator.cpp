#include "map_allocator.h"
#include <iostream>


template <typename T>
T* MapAllocator<T>::allocate(std::size_t n)
{
	auto p = std::malloc(n * sizeof(T));

	if(0 == p)
	{
		throw std::bad_alloc();
	}

	return reinterpret_cast<T*>(p);
}

template<typename T>
template <typename U, typename ...Args>
void MapAllocator<T>::construct(U* p, Args&&... args)
{

}


template <typename T>
void MapAllocator<T>::destroy(T* p)
{

}


template <typename T>
void MapAllocator<T>::deallocate(T* p, std::size_t n)
{
	std::free(p);
}