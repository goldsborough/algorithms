#ifndef HEAP_SORT_SINGLE_FUNCTION_HPP
#define HEAP_SORT_SINGLE_FUNCTION_HPP

#include <algorithm>

template<typename Iterator>
void sink(Iterator begin, Iterator iterator, Iterator end)
{
	while (iterator < end)
	{
		auto left = iterator + std::distance(begin, iterator);
		
		if (left >= end) return;
		
		auto right = left + 1;
		
		Iterator child;
		
		if (right >= end || *left > *right) child = left;
		
		else child = right;
		
		if (*child <= *iterator) break;
		
		std::swap(*iterator, *child);
		
		iterator = child;
	}
}

template<typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
	if (begin == end) return;
	
	auto i = begin + std::distance(begin, end)/2;
	
	for (auto stop = std::prev(begin); i != stop; --i)
	{
		sink(begin, i, end);
	}
	
	for (--end; begin != end; --end)
	{
		std::swap(*begin, *end);
		
		sink(begin, begin, end);
	}
}

#endif /* HEAP_SORT_SINGLE_FUNCTION_HPP */