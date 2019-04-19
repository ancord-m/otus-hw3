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

	pointer storage				{ nullptr }; //const?
	pointer storage_begin 		{ nullptr };
	pointer storage_end 		{ nullptr };
	pointer storage_iterator 	{ nullptr };
	

	MapAllocator(unsigned int storage_capacity)
	{
		this->storage_capacity = storage_capacity;				
	//	std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
	}

	template<typename U>
	MapAllocator(const MapAllocator<U> &other)
	{
		this->storage_capacity = other.storage_capacity;
	//	std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
	}

	pointer allocate(std::size_t n)
	{
		if(!spaceIsAllocated())
		{
			allocateSpaceForStorage();
			storage_iterator = storage; 
		}

		increaseElementsQuantity();

		//return storage;
		return pointerForNextElement();


		//ПЕРЕНЕСИ ИСКЛЮЧЕНИЕ В allocateSpaceForStorage
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
	//	std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
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

		decreaseElementsQuantity();

		if(noElementsInStorage() & spaceIsAllocated())
		{
			std::free(storage);
		}
	}

	private:
		bool spaceIsAllocated(void)
		{
			return storage != nullptr;
		}

		void allocateSpaceForStorage(void)
		{
			//кдиать bad_alloc
			storage = reinterpret_cast<pointer>(std::malloc(storage_capacity * sizeof(value_type)));
		}

		pointer pointerForNextElement(void)
		{
			//можно бросать исключение, если storage_iterator == storage_end
			return storage_iterator++;
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

		template<typename C>
		void printer(std::string msg, C content)
		{
			std::cout << msg + ": " << content << std::endl;
		}
};