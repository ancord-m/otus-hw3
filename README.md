Важные мысли по аллокатору:
1. Пробросить числовой параметр N, который обеспечет резервацию памяти для N элементов того, что собираемся хранить, можно только двумя способоами:
 - параметр шаблона
 - через конструктор аллокатора

2. Интересно наблюдать через _PRETTY_FUNCTION_ как стандартный контейнер map вызывает конструкторы и деструкторы моего аллокатора.

3. allocator_traits - это интерфейсный класс свойств, через который принято доставать что?
почему не пишем value_type *? потому что получаем доступ через интерфейсный класс свойств allocator_traits
4. rebind

5. Метод allocate принимает ненужный в данном случае параметр n типа size_t. У нас уже есть storage_capacity, поэтому просто удовлетворяем требования интерфейса.

6. 	using listnode_allocator_type = typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type>;
	строка выше идентична нижеследующему:
	using listnode_allocator_type = typename allocator_type :: template rebind<value_type>     ::          other;
	перевод на человеческий:
	      listnode_allocator_type =        MapAllocator     :: template rebind<ListNode<int>>  ::   MapAllocator<ListNode<int>
	        						       'allocator_type'          'struct rebind'                        'other'
	то есть listnode_allocator_type - это тип MapAllocator<ListNode<int>>

7. я так и не понял, почему это работает в деструкторе:

	for(auto it = this->begin(); it != this->end(); ++it)
	{
		ListNodeAllocator.destroy(&(*it));
		ListNodeAllocator.deallocate(&(*it), MEMORY_FOR_ONE_NODE);
	}	

	по сути, под &(\*it) кроется конкретный узел вместе с указателем next на следующий.
	вопрос: каким образом мой оператор++ у итератора контейнера List обеспечивает 
	корректный переход на next ListNode ПОСЛЕ вызова free стандартным аллокатором ???

8.  Забавный момент с итератором: последовательность - это абстракция. Нечто, что можно перебрать от начала и до конца. End дает конец последовательности, как нечто, что указывает на воображаемый элемент, следующий за последним элементом в последовательности. То есть, по-русски, nullptr в ListNode::next члене.