#ifndef ELEMENTARY_HPP
#define ELEMENTARY_HPP

#include <cstddef>
#include <iterator>
#include <utility>

template<typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
	if (begin == end) return;
	
	auto stop = std::prev(begin);
	
	for (++begin; begin != end; ++begin)
	{
		auto value = *begin;
		
		auto j = begin, i = std::prev(begin);
		
		for ( ; i != stop && *i > value; --i, --j) *j = *i;
		
		*j = value;
	}
}

template<typename Iterator>
void selection_sort(Iterator begin, Iterator end)
{
	if (begin == end) return;
	
	for ( ; begin != end; ++begin)
	{
		auto min = begin;
		
		for (auto i = std::next(begin); i != end; ++i)
		{
			if (*i < *min) min = i;
		}
		
		std::swap(*begin, *min);
	}
}


template<typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
	for (auto i = begin; i != end; ++i)
	{
		for (auto j = begin, k = std::next(begin); k != end; ++j, ++k)
		{
			if (*j > *k) std::swap(*j, *k);
		}
	}
}


template<typename Iterator>
void shell_sort(Iterator begin, Iterator end)
{
	std::size_t stride = 1;
	
	auto stop = std::distance(begin, end)/3;
	
	while (stride <= stop)
	{
		stride = 3 * stride + 1;
	}
	
	for ( ; stride > 0; stride /= 3)
	{
		for (auto i = begin + stride; i < end; i += stride)
		{
			auto value = *i;
			
			auto k = i, j = i - stride;
			
			for ( ; j >= begin && *j > value; j -= stride, k -= stride)
			{
				*k = *j;
			}
			
			*k = value;
		}
	}
}



#endif /* ELEMENTARY_HPP */