#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <iterator>
#include <vector>
#include <utility>

template<typename T>
struct Node
{
	Node(const T& data_, Node* next_ = nullptr)
	: data(data_)
	, next(next_)
	{ }
	
	T data;
	
	Node* next;
};


template<typename Node>
Node* kth_to_last(Node* node, std::size_t k)
{
	auto hare = node;
	
	for (std::size_t i = 0; i <= k; ++i)
	{
		if (! hare) return nullptr;
		
		hare = hare->next;
	}
	
	while (hare)
	{
		node = node->next;
		hare = hare->next;
	}
	
	return node;
}

template<typename Node>
Node* _recursive_kth_to_last(Node* node, std::size_t& k)
{
	if (! node) return nullptr;
	
	auto result = _recursive_kth_to_last(node->next, k);
	
	if (result) return result;
	
	if (k-- == 0) return node;
	
	return nullptr;
}


template<typename Node>
Node* recursive_kth_to_last(Node* node, std::size_t k)
{
	return _recursive_kth_to_last(node, k);
}


template<typename Node>
void delete_given_node(Node* node)
{
	if (! node) return;
	
	if (node->next)
	{
		auto next = node->next;
		
		std::swap(node->data, next->data);
		
		node->next = next->next;
		
		delete next;
	}
	
	else delete node;
}

template<typename Node, typename T>
Node* partition_list(Node* node, const T& pivot)
{
	if (! node || ! node->next) return node;
	
	auto next = node->next;
	
	Node* first = node;
	Node* last = node;
	
	node->next = nullptr;
	
	for (node = next; node; )
	{
		next = node->next;
		
		if (node->data <= pivot)
		{
			node->next = first;
			first = node;
		}
		
		else
		{
			last->next = node;
			last = node;
			
			last->next = nullptr;
		}
		
		node = next;
	}
	
	return first;
}

template<typename Node, typename T>
void partition_list2(Node* node, const T& pivot)
{
	if (! node || ! node->next) return;
	
	for (auto left = node; node; node = node->next)
	{
		if (node->data < pivot)
		{
			std::swap(left->data, node->data);
			
			left = left->next;
		}
	}
}

template<typename Node>
Node* loop_start(Node* node)
{
	if (! node || ! node->next) return nullptr;
	
	auto hare = node->next;
	
	for (auto turtle = node; hare && hare->next; turtle = turtle->next, hare = hare->next)
	{
		if (turtle == hare) break;
	}
	
	if (! hare || ! hare->next) return nullptr;
	
	while (node != hare)
	{
		node = node->next;
		hare = hare->next;
	}
	
	return node;
}

template<typename Node>
bool has_loop(Node* turtle)
{
	if (! turtle || ! turtle->next) return false;
	
	for (auto hare = turtle->next;
		 hare && hare->next;
		 turtle = turtle->next, hare = hare->next->next)
	{
		if (hare == turtle) return true;
	}
	
	return false;
}

template<typename Node>
bool _is_palindrome(Node* left, Node*& right, bool& move_back)
{
	if (left != right)
	{
		if (! _is_palindrome(left->next, right, move_back)) return false;
	}
	
	if (! move_back)
	{
		if (left->data != right->data) return false;
		
		right = right->next;
	}
	
	else move_back = false;
	
	return true;

}

template<typename Node>
bool is_palindrome(Node* node)
{
	if (! node || ! node->next) return false;
	
	auto turtle = node;
	auto hare = node;
	
	std::size_t count = 0;
	
	while (hare)
	{
		turtle = turtle->next;
		hare = hare->next->next;
		
		++count;
	}
	
	bool move_back = count % 2 == 0;
	
	return _is_palindrome(node, turtle, move_back);
}

template<typename Node, typename T>
void _recursive_partition_list(Node* first, Node* last, const T& pivot)
{
	if (! last) return;
	
	if (first->data < pivot) first = first->next;
	
	_recursive_partition_list(first, last->next, pivot);

	if (last->data <= pivot)
	{
		std::swap(first->data, last->data);
	}
}

template<typename Node, typename T>
Node* recursive_partition_list(Node* node, const T& pivot)
{
	_recursive_partition_list(node, node, pivot);
	
	return node;
}

template<typename Node>
Node* reverse_list(Node* node)
{
	if (! node || ! node->next) return node;
	
	Node* previous = nullptr;
	Node* next = nullptr;
	
	while (node)
	{
		next = node->next;
		
		node->next = previous;
		
		previous = node;
		node = next;
	}
	
	return previous;
}

template<typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
Node<T>* make_list(Iterator begin, Iterator end)
{
	if (begin == end) return nullptr;
	
	Node<T>* first = nullptr;
	Node<T>* node = nullptr;
	
	for ( ; begin != end; ++begin)
	{
		auto next = new Node<T>(*begin);
		
		if (node) node->next = next;
		
		else first = next;
		
		node = next;
	}
	
	return first;
}

template<typename T = int>
Node<T>* make_list(const std::vector<int>& values)
{
	return make_list(values.begin(), values.end());
}

template<typename Node, typename Function>
void apply_to_list(Node* node, Function function)
{
	for ( ;node; node = node->next)
	{
		function(node->data);
	}
}

template<typename Node>
void delete_list(Node* node)
{
	while (node)
	{
		auto next = node->next;
		
		delete node;
		
		node = next;
	}
}

#endif /* LINKED_LIST_HPP */