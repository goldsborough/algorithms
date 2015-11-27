#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <algorithm>

template<typename Iterator>
class HeapSort
{
public:
	
	void operator()(Iterator begin, Iterator end)
	{
		for (auto stop = std::prev(begin), i = begin + std::distance(begin, end)/2;
			 i != stop;
			 --i)
		{
			_sink(begin, i, end);
		}
		
		for (--end; begin != end; --end)
		{
			std::swap(*begin, *end);
			
			_sink(begin, begin, end);
		}
	}
	
private:
	
	Iterator _left_child(Iterator begin, Iterator iterator)
	{
		return iterator + std::distance(begin, iterator);
	}
	
	Iterator _right_child(Iterator begin, Iterator iterator)
	{
		return _left_child(begin, iterator) + 1;
	}
	
	Iterator _parent(Iterator begin, Iterator iterator)
	{
		if (iterator == begin) return begin;
		
		return begin + std::distance(begin, iterator)/2;
	}
	
	void _sink(Iterator begin, Iterator iterator, Iterator end)
	{
		while (iterator < end)
		{
			auto left = _left_child(begin, iterator);
			
			if (left >= end) return;
			
			auto right = _right_child(begin, iterator);
			
			Iterator child;
			
			if (right >= end || *left > *right) child = left;
			
			else child = right;
			
			if (*child <= *iterator) break;
			
			std::swap(*child, *iterator);
			
			iterator = child;
		}
	}
};

template<typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
	HeapSort<Iterator> sort;
	
	sort(begin, end);
}

#endif /* HEAP_SORT_HPP */