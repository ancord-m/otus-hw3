#include <memory>
#include <iostream>

template <typename T>
struct ListNode
{
	T value;
	ListNode<T>* next;

	ListNode(const T& v) : value(v) { };
};

template <typename T, typename Allocator = std::allocator<T>>
struct List
{
	using allocator_type = Allocator;
	using size_type = std::size_t;
	using value_type = ListNode<T>;
	using reference = value_type&;
	using const_reference = const value_type&;
	//почему не  value_type *? потому что получаем доступ через интерфейсный класс свойств allocator_traits
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

	using node_allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<value_type>;
	/*
	строка выше идентична нижеследующему:
	using ListNodeAllocator = typename allocator_type::template rebind<value_type>::other;
	перевод:   MapAllocator    ::  template rebind<ListNode<int>>  ::   MapAllocator<ListNode<int>
	         'allocator_type'       'struct rebind'                        'other'
	*/

	
	node_allocator_type ListNodeAllocator;
	pointer p;

	explicit List(const allocator_type& a)
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
		
		ListNodeAllocator = node_allocator_type{a};
		
		//*al = ListNodeAllocator{a};
	}


	/*List(const allocator_type &alc) //: a (alc)
	{

		p = b.allocate(1);
		//p = ListNodeAllocator::allocate(1);


	}*/
	void test()
	{
		std::cout << "tag" << std::endl;
		std::cout << ListNodeAllocator.storage_capacity << std::endl;
	}

	~List()
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;
	//	b.deallocate(p, 1);
		//ListNodeAllocator::deallocate(p, 1);
	}

	decltype(auto) push(T&& value)
	{
		auto p = ListNodeAllocator.allocate(1);
		ListNodeAllocator.construct(p, value);
		return p;
	}
};


/*
Как бы я сделал Лист без аллокатора:
1. В конструкторе провел бы только инициализацию
2. Ввел бы метод reserve или работал бы без него
3. В методе push выделял бы память под новый элемент или 
просто складывал бы его в готовую ячейку. Тут нужен указатель
4. В ходе обхода смещал бы указатель по хранилищу и вытаскивал элемент. Нужен итератор
*/