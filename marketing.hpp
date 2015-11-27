#ifndef MARKETING_HPP
#define MARKETING_HPP

#include <vector>
#include <sstream>
#include <string>

/*
 You work for a very large company that markets many different products. In some cases, one product you market competes with another. To help deal with this situation you have split the intended consumers into two groups, namely Adults and Teenagers. If your company markets 2 products that compete with each other, selling one to Adults and the other to Teenagers will help maximize profits. Given a list of the products that compete with each other, you are going to determine whether all can be marketed such that no pair of competing products are both sold to Teenagers or both sold to Adults. If such an arrangement is not feasible your method will return -1. Otherwise, it should return the number of possible ways of marketing all of the products.
 
 
 
 The products will be given in a String[] compete whose kth element describes product k. The kth element will be a single-space delimited list of integers. These integers will refer to the products that the kth product competes with. For example:
 compete = {"1 4",
 "2",
 "3",
 "0",
 ""}
 The example above shows product 0 competes with 1 and 4, product 1 competes with 2, product 2 competes with 3, and product 3 competes with 0. Note, competition is symmetric so product 1 competing with product 2 means product 2 competes with product 1 as well.
 
 Ways to market:
 
 1) 0 to Teenagers, 1 to Adults, 2 to Teenagers, 3 to Adults, and 4 to Adults
 
 2) 0 to Adults, 1 to Teenagers, 2 to Adults, 3 to Teenagers, and 4 to Teenagers
 
 Your method would return 2.

*/

class Graph
{
public:
	
	enum class MarketedTo
	{
		None,
		Teenagers,
		Adults
	};
	
	struct Vertex
	{
		Vertex(std::size_t vertex_,
			   MarketedTo marketed_ = MarketedTo::None)
		: vertex(vertex_)
		, marketed(marketed_)
		{ }
		
		std::size_t vertex;
		
		MarketedTo marketed;
	};
	
	using adjacent_t = std::vector<Vertex>;
	
	Graph(const std::vector<std::string>& products)
	: _vertices(products.size())
	{
		for (std::size_t i = 0; i < products.size(); ++i)
		{
			adjacent_t adjacent;
			
			std::istringstream stream(products[i]);
			
			std::size_t competitor;
			
			while (stream >> competitor)
			{
				adjacent.push_back(competitor);
				
				_vertices[competitor].push_back(i);
			}
			
			_vertices[i] = adjacent;
		}
	}
	
	adjacent_t& operator[](const Vertex& vertex)
	{
		return _vertices.at(vertex.vertex);
	}
	
	const adjacent_t& operator[](const Vertex& vertex) const
	{
		return _vertices.at(vertex.vertex);
	}
	
	std::size_t vertex_number() const
	{
		return _vertices.size();
	}
	
private:
	
	std::vector<adjacent_t> _vertices;
};

class Components
{
public:
	
	using component_t = Graph::adjacent_t;
	
	using iterator = std::vector<component_t>::const_iterator;
	
	Components(const Graph& graph)
	{
		std::vector<bool> visited(graph.vertex_number());
		
		for (std::size_t vertex = 0; vertex < graph.vertex_number(); ++vertex)
		{
			if (! visited[vertex])
			{
				component_t component;
				
				_dfs(graph, vertex, component, visited);
				
				_components.push_back(component);
			}
		}
	}
	
	
	iterator begin() const
	{
		return _components.cbegin();
	}
	
	iterator end() const
	{
		return _components.cend();
	}
	
	const std::vector<component_t>& components() const
	{
		return _components;
	}
	
	std::size_t number()
	{
		return _components.size();
	}
	
private:
	
	void _dfs(const Graph& graph,
			  std::size_t vertex,
			  component_t& component,
			  std::vector<bool>& visited)
	{
		if (visited[vertex]) return;
		
		visited[vertex] = true;
		
		component.push_back(vertex);
		
		for (const auto& adjacent : graph[vertex])
		{
			_dfs(graph, adjacent.vertex, component, visited);
		}
	}
	
	std::vector<component_t> _components;
};

Graph::MarketedTo other(Graph::MarketedTo group)
{
	if (group == Graph::MarketedTo::None)
	{
		throw std::invalid_argument("Has no opposite!");
	}
	
	else if (group == Graph::MarketedTo::Teenagers)
	{
		return Graph::MarketedTo::Adults;
	}
	
	else return Graph::MarketedTo::Teenagers;
}

bool is_bipartite(Graph& graph,
				  const Graph::Vertex& vertex,
				  std::vector<bool>& visited)
{
	if (visited[vertex.vertex]) return true;
	
	visited[vertex.vertex] = true;
	
	for (auto& adjacent : graph[vertex])
	{
		if (adjacent.marketed == Graph::MarketedTo::None)
		{
			adjacent.marketed = other(vertex.marketed);
		}
		
		else if (adjacent.marketed == vertex.marketed) return false;
	}
	
	for (const auto& adjacent : graph[vertex])
	{
		if (! is_bipartite(graph, adjacent, visited))
		{
			return false;
		}
	}
	
	return true;
}

int marketing_strategies(const std::vector<std::string>& products)
{
	Graph graph(products);
	
	int units = 0;
	
	std::vector<bool> visited(graph.vertex_number());
	
	for (const auto& component : Components(graph))
	{
		if (component.empty()) ++units;
		
		auto vertex = component.front();
		
		vertex.marketed = Graph::MarketedTo::Teenagers;
		
		if (is_bipartite(graph, vertex, visited)) ++units;
		
		else return -1;
	}
	
	return 1 << units;
}

#endif /* MARKETING_HPP */