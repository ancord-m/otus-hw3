#include <cstddef>
#include <iostream>

template <typename T>
struct MapAllocator
{
	using value_type = T;

	T* allocate(std::size_t n)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		auto p = std::malloc(n * sizeof(T));

		if(0 == p)
		{
			throw std::bad_alloc();
		}

		return reinterpret_cast<T*>(p);
	}


	template <typename U, typename ...Args>
	void construct(U* p, Args&&... args)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		new(p) T(std::forward<Args>(args)...);
	}

	void destroy(T* p)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		p->~T();
	}

	void deallocate(T* p, std::size_t n)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		std::free(p);
	}
};