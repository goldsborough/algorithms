#ifndef MERGE_SORT_SINGLE_FUNCTION_HPP
#define MERGE_SORT_SINGLE_FUNCTION_HPP

#include <assert.h>
#include <algorithm>
#include <iterator>
#include <vector>

template<typename Iterator,
		 typename T = typename std::iterator_traits<Iterator>::value_type>
void merge_sort(Iterator begin, Iterator end)
{
	auto distance = std::distance(begin, end);
	
	if (distance < 2) return;
	
	distance /= 2;
	
	auto middle = begin;
	
	std::advance(middle, distance);
	
	merge_sort(begin, middle);
	merge_sort(middle, end);
	
	if (*middle < *std::prev(middle))
	{
		std::vector<T> auxiliary(begin, end);
		
		auto i = auxiliary.begin();
		
		auto j = i;
		
		std::advance(j, distance);
		
		for (auto stop = j; begin != end; ++begin)
		{
			if ((j == auxiliary.end()) || (i != stop && *i <= *j))
			{
				*begin = *i++;
			}
			
			else *begin = *j++;
		}
	}
}

template<typename Sequence>
void merge_sort(Sequence& sequence, std::size_t begin, std::size_t end)
{
	auto distance = end - begin;
	
	if (distance < 2) return;
	
	auto middle = begin + distance/2;
	
	merge_sort(sequence, begin, middle);
	merge_sort(sequence, middle, end);
	
	if (sequence[middle] < sequence[middle - 1])
	{
		using T = std::remove_reference_t<decltype(sequence[begin])>;
		
		auto offset = std::begin(sequence);
		
		std::vector<T> auxiliary(offset + begin, offset + end);
		
		middle -= begin;
		
		for (size_t i = 0, j = middle; begin < end; ++begin)
		{
			if ((j == auxiliary.size()) ||
				(i != middle && auxiliary[i] <= auxiliary[j]))
			{
				sequence[begin] = auxiliary[i++];
			}
			
			else sequence[begin] = auxiliary[j++];
		}
	}
}

#endif /* MERGE_SORT_SINGLE_FUNCTION_HPP */