#include <cstddef>
#include <iostream>

template <typename T>
struct MapAllocator
{
	using value_type = T;
	using pointer    = T*;
	using reference  = T&;

	template<typename U>
	struct rebind
	{
		typedef MapAllocator<U> other;
	};

	pointer allocate(std::size_t n)
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
	//template <typename U, typename X>
	//void construct(U* p, X x)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	//	new(p) T(std::forward<Args>(args)...);
	//	new(p) T(std::forward<X>(x));

	}

	void destroy(pointer p)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		//p->~T();
	}

	void deallocate(pointer p, std::size_t n)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		std::free(p);
	}
};