#include <cstddef>
#include <iostream>

template <typename T>
struct MapAllocator
{
	using size_type			= std::size_t;
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

	template<typename U>
	using rebind_alloc		= typename MapAllocator::template rebind<U>::other;

	static const size_type DEFAULT_ELEMENTS_QUANTITY = 1;

	unsigned int storage_capacity { 0 };
	unsigned int elements_counter { 0 };

	pointer storage_begin		{ nullptr };
	pointer storage_end 		{ nullptr };
	pointer storage_iterator 	{ nullptr };
	
	MapAllocator() = default;

	MapAllocator(unsigned int storage_capacity)
	{							
		this->storage_capacity = storage_capacity;
	}

	template<typename U>
	MapAllocator(const MapAllocator<U> &other)
	{
		this->storage_capacity = other.storage_capacity;
	}

	MapAllocator(const MapAllocator& other)
	{
		this->storage_capacity = other.storage_capacity;
	}

	~MapAllocator()	= default;

	pointer allocate(size_type n = DEFAULT_ELEMENTS_QUANTITY)
	{
		if(!spaceIsAllocated())
		{
			allocateSpaceForStorage();
			initIterator();
		}

		increaseElementsQuantity();

		return getPointerToNextFreeMemoryCell();
	}

	template <typename U, typename ...Args>
	void construct(U* p, Args&&... args)
	{
		new(p) U(std::forward<Args>(args)...);
	}

	void destroy(pointer p)
	{
		p->~T();
	}

	void deallocate(pointer p, size_type n = DEFAULT_ELEMENTS_QUANTITY)
	{
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

		pointer getPointerToNextFreeMemoryCell(void)
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