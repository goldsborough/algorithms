#ifndef MAXIMUM_SUBARRAY_HPP
#define MAXIMUM_SUBARRAY_HPP

#include <iterator>
#include <vector>

template<typename Iterator>
auto maximum_subarray(Iterator begin, Iterator end) -> decltype(*begin + *begin)
{
	using T = typename std::iterator_traits<Iterator>::value_type;
	
	T best = 0;
	T current = 0;
	
	for ( ; begin != end; ++begin)
	{
		current += *begin;
		
		if (current > best) best = current;
			
			else if (current < 0) current = 0;
				}
	
	return best;
}

template<typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
T maximum_subarray_bad(Iterator begin, Iterator middle, Iterator end)
{
	T best_left = 0;
	T left_sum = 0;
	
	for (auto stop = std::prev(begin), i = std::prev(middle);
		 i != stop;
		 --i)
	{
		left_sum += *i;
		
		if (left_sum > best_left)
		{
			best_left = left_sum;
		}
	}

	T best_right = 0;
	T right_sum = 0;
	
	for (auto i = std::next(middle); i != end; ++i)
	{
		right_sum += *i;
		
		if (right_sum > best_right)
		{
			best_right = right_sum;
		}
	}
	
	if (best_left == 0 && best_right == 0 && *middle < 0) return 0;
	
	return best_left + *middle + best_right;
}

template<typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
T best_profit(Iterator begin, Iterator end)
{
	// edge casees
	
	if (begin == end) return 0;
	
	else if (std::next(begin) == end) return *begin;
	
	auto middle = begin;
	
	std::advance(middle, std::distance(begin, end)/2);
	
	auto best = maximum_subarray_bad(begin, middle, end);
	
	auto left = best_profit(begin, middle);
	
	if (left > best) best = left;
	
	auto right = best_profit(middle, end);
	
	if (right > best) best = right;
	
	return best;
}

std::size_t best_profit(std::vector<int>& stock)
{
	for (std::size_t i = stock.size() - 1; i > 0; --i)
	{
		stock[i] -= stock[i - 1];
	}
	
	return best_profit(std::next(stock.begin()), stock.end());
}
#endif /* MAXIMUM_SUBARRAY_HPP */