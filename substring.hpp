#ifndef SUBSTRING_HPP
#define SUBSTRING_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <unordered_set>

template<typename Iterator>
std::size_t search_for_substrings(const std::string& string,
								  Iterator begin,
								  Iterator end)
{
	if (begin == end) return 0;
	
	std::unordered_set<std::size_t> sizes;
	
	std::unordered_set<std::string> substrings;
	
	for (auto i = begin; i != end; ++i)
	{
		if (! sizes.count(i->length()))
		{
			for (auto j = string.begin(), k = string.begin() + i->length(), stop = std::next(string.end());
				 k != stop;
				 ++j, ++k)
			{
				substrings.insert(std::string(j, k));
			}
		}
	}
	
	std::size_t count = 0;
	
	for ( ; begin != end; ++begin)
	{
		if (substrings.count(*begin)) ++count;
	}
	
	return count;
}

class SuffixTree
{
public:
	
	SuffixTree(const std::string& string)
	: _root(nullptr)
	{
		insert(string);
		
		for (auto i = std::next(string.begin()), end = string.end();
			 i != end;
			 ++i)
		{
			insert(std::string(i, end));
		}
	}
	
	~SuffixTree()
	{
		_clear(_root);
	}
	
	void insert(const std::string& string)
	{
		_root = _insert(_root, string);
	}
	
	bool contains(const std::string& target)
	{
		return _contains(_root, target);
	}
	
private:
	
	struct Node
	{
		Node()
		{
			std::fill(next.begin(), next.end(), nullptr);
		}
		
		std::array<Node*, 26> next;
	};
	
	Node* _insert(Node* node,
				  const std::string& string,
				  std::size_t index = 0)
	{
		if (! node) node = new Node;
		
		if (index == string.length()) return node;
		
		auto& next = node->next[string[index] - 97];
		
		next = _insert(next, string, ++index);
		
		return node;
	}
	
	bool _contains(Node* node,
				   const std::string& target,
				   std::size_t index = 0) const
	{
		if (! node) return false;
		
		if (index == target.length()) return true;
		
		auto& next = node->next[target[index] - 97];
		
		return _contains(next, target, ++index);
	}
	
	void _clear(Node* node)
	{
		if (! node) return;
		
		for (auto& next : node->next) _clear(next);
		
		delete node;
	}
	
	Node* _root;
};

template<typename Iterator>
std::size_t search_for_substrings2(const std::string& string,
								  Iterator begin,
								  Iterator end)
{
	if (begin == end) return 0;
	
	SuffixTree tree(string);
	
	std::size_t count = 0;
	
	for ( ; begin != end; ++begin)
	{
		if (tree.contains(*begin)) ++count;
	}
	
	return count;
}

#endif /* SUBSTRING_HPP */