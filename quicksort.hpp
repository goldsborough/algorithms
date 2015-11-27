#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>
#include <random>

template<typename Iterator>
class QuickSort
{
public:
	
	static const std::size_t cutoff = 10;
	
	void operator()(Iterator begin, Iterator end)
	{
		if (std::distance(begin, end) < cutoff)
		{
			_shuffle(begin, end);
			
			_sort(begin, end);
		}
	
		_insertion_sort(begin, end);
	}
	
private:
	
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
	
	void _shuffle(Iterator begin, Iterator end)
	{
		using distribution_t = std::uniform_int_distribution<std::size_t>;
		
		static std::random_device seed;
		static std::mt19937 generator(seed());
		
		if (begin == end) return;
		
		std::size_t distance = 1;
		
		for (auto i = std::next(begin); i != end; ++i, ++distance)
		{
			distribution_t distribution(0, distance);
			
			auto other = begin;
			
			std::advance(other, distribution(generator));
			
			if (i != other) std::swap(*i, *other);
		}
	}
	
	void _sort(Iterator begin, Iterator end)
	{
		if (std::distance(begin, end) < cutoff) return;
		
		auto pivot = _partition(begin, end);
		
		_sort(begin, pivot);
		_sort(++pivot, end);
	}
	
	void _sort3(Iterator begin, Iterator end)
	{
		if (std::distance(begin, end) < cutoff) return;
		
		auto range = _partition3(begin, end);
		
		_sort(begin, range.first);
		_sort(range.second, end);
	}
	
	Iterator _partition(Iterator begin, Iterator end)
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
	
	std::pair<Iterator, Iterator>
	_partition3(Iterator begin, Iterator end)
	{
		auto pivot = begin++;
		
		if (pivot == end || begin == end) return {pivot, pivot};
		
		auto i = begin;
		
		for (--end; i != std::next(end); )
		{
			if (*i < *pivot)
			{
				if (i != begin) std::swap(*begin, *i);
				
				++begin;
				++i;
			}
			
			else if (*i > *pivot)
			{
				if (i != end) std::swap(*i, *end);
				
				--end;
			}
			
			else ++i;
		}
		
		std::swap(*pivot, *(--begin));
		
		return {begin, i};
	}
};

template<typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
	QuickSort<Iterator> sort;
	
	sort(begin, end);
}

#endif /* QUICK_SORT_HPP */