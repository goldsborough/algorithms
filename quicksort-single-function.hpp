#ifndef QUICK_SORT_SINGLE_FUNCTION_HPP
#define QUICK_SORT_SINGLE_FUNCTION_HPP

#include <algorithm>
#include <assert.h>
#include <iterator>
#include <utility>

template<typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
	auto i = std::next(begin);
	
	if (begin == end || i == end) return;
	
	for (auto j = std::prev(end); i != j; ++i)
	{
		while (i != j && *i < *begin) ++i;
		
		while (i != j && *j > *begin) --j;
		
		if (i == j) break;
		
		std::swap(*i, *j);
	}
	
	if (*i > *begin) --i;
	
	std::swap(*begin, *i);
	
	quick_sort(begin, i);
	
	quick_sort(++i, end);
	
	assert(std::is_sorted(begin, end));
}

#endif /* QUICK_SORT_SINGLE_FUNCTION_HPP */