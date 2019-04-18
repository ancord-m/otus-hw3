#include <cstddef>
#include <iostream>

template <typename T>
struct MapAllocator
{
	using value_type 		= T;
	using pointer    		= T*;
	using const_pointer		= const T*;
	using reference  		= T&;
	using const_reference	= const T&;

	template<typename U>
	struct rebind
	{
		typedef MapAllocator<U> other;
	};

	unsigned int elements_quantity;
	pointer storage;


	MapAllocator(unsigned int elements_quantity)
	{
		this->elements_quantity = elements_quantity;
		storage = nullptr;

		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
	}

	template<typename U>
	MapAllocator(const MapAllocator<U> &other)
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
	}

	pointer allocate(std::size_t n)
	{
		//if(!storage)
	//	{
		std::cout << storage<< std::endl;

			std::cout << "Empty" << std::endl;

			storage = reinterpret_cast<pointer>(std::malloc(elements_quantity * sizeof(value_type)));
std::cout << storage<< std::endl;

	//	}

		return storage;

		//if(!storage)
		/*	std::cout << storage<< std::endl;

		std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		auto p = std::malloc(n * sizeof(value_type));

		if(0 == p)
		{
			throw std::bad_alloc();
		}

		return reinterpret_cast<pointer>(p);*/
	}


	template <typename U, typename ...Args>
	void construct(U* p, Args&&... args)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		new(p) U(std::forward<Args>(args)...);

	}

	void destroy(pointer p)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		p->~T();
	}

	void deallocate(pointer p, std::size_t n)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		std::free(p);
	}
};