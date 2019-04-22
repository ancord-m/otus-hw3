#include <memory>
#include <iostream>

template <typename T>
struct ListNode
{
	T value;
	ListNode<T>* next;
};

template <typename T, typename Allocator = std::allocator<T>>
class List
{
	using allocator_type = Allocator;
	using pointer = typename allocator_type::pointer;

	//typedef Allocator allocator_type;
	allocator_type a;
	pointer p;
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