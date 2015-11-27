#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>

class MergeSort
{
public:
	
	static const std::size_t cutoff = 10;
	
	template<typename Iterator>
	void operator()(Iterator begin, Iterator end)
	{
		if (begin == end) return;
		
		if (std::distance(begin, end) < cutoff)
		{
			_insertion_sort(begin, end);
		}
		
		else
		{
			using T = typename std::iterator_traits<Iterator>::value_type;
			
			std::vector<T> auxiliary(begin, end);
			
			_sort(begin, end, auxiliary.begin(), auxiliary.end());
		}
	}
	
private:
	
	template<typename Iterator>
	void _insertion_sort(Iterator begin, Iterator end)
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
	
	template<typename Iterator, typename Auxiliary>
	void _sort(Iterator begin,
			   Iterator end,
			   Auxiliary aux_begin,
			   Auxiliary aux_end)
	{
		auto distance = std::distance(begin, end);
		
		if (distance < 2) return;
		
		distance /= 2;
		
		auto middle = begin;
		auto aux_middle = aux_begin;
		
		std::advance(middle, distance);
		std::advance(aux_middle, distance);
		
		_sort(aux_begin, aux_middle, begin, middle);
		_sort(aux_middle, aux_end, middle, end);
		
		if (*aux_middle < *std::prev(aux_middle))
		{
			_merge(begin, end, aux_begin, aux_middle, aux_end);
		}
		
		else std::copy(aux_begin, aux_end, begin);
	}
	
	template<typename Iterator, typename Auxiliary>
	void _merge(Iterator begin,
				Iterator end,
				Auxiliary aux_begin,
				Auxiliary aux_middle,
				Auxiliary aux_end)
	{
		for (auto stop = aux_middle; begin != end; ++begin)
		{
			if ((aux_middle == aux_end) ||
				(aux_begin != stop && *aux_begin <= *aux_middle))
			{
				*begin = *aux_begin++;
			}
			
			else *begin = *aux_middle++;
		}
	}
};

template<typename Iterator>
void merge_sort(Iterator begin, Iterator end)
{
	MergeSort sort;
	
	sort(begin, end);
}

#endif /* MERGE_SORT_HPP */