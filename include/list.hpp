#include <memory>
#include <iostream>
#include <iterator>

template <typename T>
struct ListNode
{
	T value;
	ListNode<T>* next;

	ListNode(const T& v) : value(v), next(nullptr) { };

	friend std::ostream& operator<<(std::ostream& out, const ListNode<T>& node) 
	{
		out << node.value;

		return out;
	};
};

template <typename T, typename Allocator = std::allocator<T>>
class List
{
	using size_type = std::size_t;
	using value_type		= ListNode<T>;

	using allocator_type 	= Allocator;
	using listnode_allocator_type 
							= typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type>;

	using pointer 			= typename std::allocator_traits<listnode_allocator_type>::pointer;
	//using const_pointer 	= typename std::allocator_traits<listnode_allocator_type>::const_pointer;

	
	//using reference = value_type&;
	//using const_reference = const value_type&;
	static const size_type MEMORY_FOR_ONE_NODE = 1;
	
	listnode_allocator_type ListNodeAllocator;
	pointer head_node;
	pointer previous_node;
	
public:

	explicit List(const allocator_type& a = allocator_type{} )
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;

		head_node 			= nullptr;
		previous_node 		= nullptr;
		ListNodeAllocator 	= listnode_allocator_type{a};
	}

	~List()
	{
		std::cout << __PRETTY_FUNCTION__ <<  std::endl << std::endl;

		pointer next_to_be_deleted;
		
		/*for(auto n : *this)
		{
			next_to_be_deleted = n->next;

			ListNodeAllocator.destroy(&n);
			ListNodeAllocator.deallocate(&n, MEMORY_FOR_ONE_NODE);
		}	*/

		for(auto it = this->begin(); it != this->end(); ++it)
		{
			ListNodeAllocator.destroy(&(*it));
			ListNodeAllocator.deallocate(&(*it), MEMORY_FOR_ONE_NODE);
		}

	
	}

	void push(T& value)
	{
		push(std::move(value));
	}

	void push(T&& value)
	{
		auto new_list_node = ListNodeAllocator.allocate(MEMORY_FOR_ONE_NODE);
		ListNodeAllocator.construct(new_list_node, value);
		
		if(head_node == nullptr)
		{
			head_node = new_list_node;
			previous_node = head_node;
		}
		else 
		{
			previous_node->next = new_list_node;
			previous_node		= new_list_node;
		}
	}

	class iterator : public std::iterator<std::forward_iterator_tag, value_type>
	{
		value_type* current_pointed_value;

		public:
			iterator() : current_pointed_value(nullptr) { };

			explicit iterator(value_type* cv) : current_pointed_value(cv) { };

			iterator& operator++ () 
			{
				current_pointed_value = current_pointed_value->next;
				return *this;
			}

			typename std::iterator_traits<iterator>::reference operator* (void)
			{
				return *current_pointed_value;
			}

			bool operator!= (const iterator& other)
			{
				return this->current_pointed_value != other.current_pointed_value;
			}
	};

	iterator begin(void)
	{
		return iterator(head_node);
	}

	iterator end(void) 
	{
		return iterator();
	}
};