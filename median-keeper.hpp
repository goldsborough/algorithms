#ifndef MEDIAN_KEEPER_HPP
#define MEDIAN_KEEPER_HPP

#include <queue>
#include <vector>

template<typename T>
class MedianKeeper
{
public:
	
	MedianKeeper() = default;
	
	MedianKeeper(std::initializer_list<T> list)
	{
		for (const auto& item : list) push(item);
	}
	
	void push(const T& item)
	{
		if (seen() > 0 && item > _median)
		{
			_right.push(item);
			
			if (_right.size() == _left.size() + 2)
			{
				_left.push(_right.top());
				
				_right.pop();
			}
		}
		
		else
		{
			_left.push(item);
			
			if (_left.size() == _right.size() + 2)
			{
				_right.push(_left.top());
				
				_left.pop();
			}
		}
		
		_median = _compute();
	}
	
	T& operator()()
	{
		return median();
	}
	
	const T& operator()() const
	{
		return median();
	}
	
	T& median()
	{
		if (is_empty())
		{
			throw std::out_of_range("No values inserted yet!s");
		}
		
		return _median;
	}
	
	const T& median() const
	{
		if (is_empty())
		{
			throw std::out_of_range("No values inserted yet!s");
		}
		
		return _median;
	}
	
	
	T pop()
	{
		auto old = _median;
		
		if (seen() % 2 == 0)
		{
			_left.pop();
			_right.pop();
		}
		
		else if (_left.size() > _right.size()) _left.pop();
		
		else _right.pop();
		
		_median = _compute();
		
		return old;
	}
	
	void clear()
	{
		_left.clear();
		_right.clear();
	}
	
	
	size_t seen() const
	{
		return _left.size() + _right.size();
	}
	
	bool is_empty() const
	{
		return seen() == 0;
	}
	
private:
	
	T _compute()
	{
		if (seen() % 2 == 0)
		{
			return (_left.top() + _right.top()) / 2;
		}
		
		else if (_left.size() > _right.size()) return _left.top();
		
		else return _right.top();
	}
	
	std::priority_queue<T> _left;
	
	std::priority_queue<T, std::vector<int>, std::greater<T>> _right;
	
	T _median;
};

#endif /* MEDIAN_KEEPER_HPP */