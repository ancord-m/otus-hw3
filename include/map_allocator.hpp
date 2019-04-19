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

	unsigned int storage_capacity { 0 };
	unsigned int elements_counter { 0 };

	pointer storage_begin		{ nullptr }; //should be const?
	pointer storage_end 		{ nullptr };
	pointer storage_iterator 	{ nullptr };
	

	MapAllocator(unsigned int storage_capacity)
	{
		//std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
		this->storage_capacity = storage_capacity;				
	}

	template<typename U>
	MapAllocator(const MapAllocator<U> &other)
	{
		//std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
		this->storage_capacity = other.storage_capacity;
	}

	pointer allocate(std::size_t n)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		
		if(!spaceIsAllocated())
		{
			allocateSpaceForStorage();
			initIterator();
		}

		increaseElementsQuantity();

		return placePointerForNewElement();
	}


	template <typename U, typename ...Args>
	void construct(U* p, Args&&... args)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;		
		new(p) U(std::forward<Args>(args)...);
	}

	void destroy(pointer p)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		p->~T();
	}

	void deallocate(pointer p, std::size_t n)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
		decreaseElementsQuantity();

		if(noElementsInStorage() & spaceIsAllocated())
		{
			std::free(storage_begin);
		}
	}

	private:
		void allocateSpaceForStorage(void)
		{
			auto p = std::malloc(storage_capacity * sizeof(value_type));

			if(0 == p)
			{
				throw std::bad_alloc();
			}

			storage_begin = reinterpret_cast<pointer>(p);
			storage_end   = storage_begin + storage_capacity;
		}

		pointer placePointerForNewElement(void)
		{
			if(storage_iterator == storage_end)
			{
				throw std::out_of_range("End of allocated memory was reached");
			}

			return storage_iterator++;
		}

		void initIterator(void)
		{
			storage_iterator = storage_begin;
		}

		bool spaceIsAllocated(void)
		{
			return storage_begin != nullptr;
		}

		void increaseElementsQuantity(void)
		{
			++elements_counter;
		}

		void decreaseElementsQuantity(void)
		{
			--elements_counter;
		}

		bool noElementsInStorage(void)
		{
			return elements_counter == 0;
		}		
};