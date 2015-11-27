#ifndef QUICK_SELECT_HPP
#define QUICK_SELECT_HPP

#include <cstddef>
#include <utility>

template<typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
	auto pivot = begin++;
	
	if (pivot == end || begin == end) return pivot;
	
	for (--end; begin != end; ++begin)
	{
		while (begin != end && *begin < *pivot) ++begin;
		
		while (begin != end && *end > *pivot) --end;
		
		if (begin == end) break;
		
		std::swap(*begin, *end);
	}
	
	if (*begin > *pivot) --begin;
	
	std::swap(*begin, *pivot);
	
	return begin;
}

template<typename Iterator>
Iterator quick_select(Iterator begin, Iterator end, std::size_t k)
{
	if (begin == end || std::next(begin) == end || k == 0) return begin;
	
	auto pivot = partition(begin, end);
	
	auto distance = std::distance(begin, pivot);
	
	if (distance < k) return quick_select(++pivot, end, k - distance - 1);
	
	else if (distance > k) return quick_select(begin, pivot, k);
	
	else return pivot;
}

#endif /* QUICK_SELECT_HPP */