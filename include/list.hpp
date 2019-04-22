#include <memory>
#include <iostream>

template <typename T, typename Allocator = std::allocator<T>>
class List
{
	typedef Allocator allocator_type;
	Allocator a;
	typename allocator_type::pointer p;
public:
	List() : a( Allocator() )
	{
		
	}

	~List()
	{
		a.deallocate(p, 1);
	}

	decltype(auto) push()
	{
		p = a.allocate(1);
		return p;
	}
};