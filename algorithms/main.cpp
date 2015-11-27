#include "quicksort.hpp"

#include <iostream>
#include <vector>

void print()
{
	std::cout << std::endl;
}

template<typename Head, typename... Tail>
void print(Head&& head, Tail&&... tail)
{
	std::cout << std::forward<Head>(head);
	
	print(std::forward<Tail>(tail)...);
}

template<typename Iterator>
void printall(Iterator begin, Iterator end)
{
	while (begin != end)
	{
		std::cout << *begin;
		
		if (++begin != end) std::cout << ", ";
	}
}

int main(int argc, const char* argv[])
{
	std::vector<int> v = {4, 2, -1, 6, 8, 9, -3};
	
	quick_sort(v.begin(), v.end());
	
	printall(v.begin(), v.end());
}