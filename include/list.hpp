#include <memory>
#include <iostream>

template <typename T>
struct ListNode
{
	T value;
	ListNode<T>* next;
};

template <typename T, typename Allocator = std::allocator<T>>
struct List
{
	using allocator_type = Allocator;
	using size_type = std::size_t;
	using value_type = ListNode<T>;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = std::allocator_traits<Allocator>::pointer;
	using const_pointer = std::allocator_traits<Allocator>::const_pointer;

	//typedef Allocator allocator_type;
	allocator_type a;
	pointer p;


/*	explicit List(const allocator_type &a = allocator_type())
	{

	}
*/

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


/*
Как бы я сделал Лист без аллокатора:
1. В конструкторе провел бы только инициализацию
2. Ввел бы метод reserve или работал бы без него
3. В методе push выделял бы память под новый элемент или 
просто складывал бы его в готовую ячейку. Тут нужен указатель
4. В ходе обхода смещал бы указатель по хранилищу и вытаскивал элемент. Нужен итератор
*/