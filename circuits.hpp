#ifndef CIRCUITS_HPP
#define CIRCUITS_HPP

#include <cstddef>
#include <sstream>
#include <vector>

/*
 An essential part of circuit design and general system optimization is critical path analysis. On a chip, the critical path represents the longest path any signal would have to travel during execution. In this problem we will be analyzing chip designs to determine their critical path length. The chips in this problem will not contain any cycles, i.e. there exists no path from one component of a chip back to itself.
 
 
 
 Given a String[] connects representing the wiring scheme, and a String[] costs representing the cost of each connection, your method will return the size of the most costly path between any 2 components on the chip. In other words, you are to find the longest path in a directed, acyclic graph. Element j of connects will list the components of the chip that can be reached directly from the jth component (0-based). Element j of costs will list the costs of each connection mentioned in the jth element of connects. As mentioned above, the chip will not contain any cyclic paths. For example:
 connects = {"1 2",
 "2",
 ""}
 costs    = {"5 3",
 "7",
 ""}
 In this example, component 0 connects to components 1 and 2 with costs 5 and 3 respectively. Component 1 connects to component 2 with a cost of 7. All connections mentioned are directed. This means a connection from component i to component j does not imply a connection from component j to component i. Since we are looking for the longest path between any 2 components, your method would return 12.
*/

class Graph
{
public:
	
	using vertex_t = short;
	
	struct Edge
	{
		using cost_t = short;
		
		Edge(vertex_t vertex_ = 0,
			 cost_t cost_ = 0)
		: vertex(vertex_)
		, cost(cost_)
		{ }
		
		vertex_t vertex;
		
		cost_t cost;
	};
	
	using adjacent_t = std::vector<Edge>;
	
	Graph(const std::vector<std::string>& components,
		  const std::vector<std::string>& costs)
	: _vertices(components.size())
	{
		for (std::size_t vertex = 0; vertex < components.size(); ++vertex)
		{
			std::istringstream component_stream(components[vertex]);
			std::istringstream cost_stream(costs[vertex]);
			
			adjacent_t adjacent;
			
			Edge edge;
			
			while (component_stream >> edge.vertex)
			{
				cost_stream >> edge.cost;
				
				adjacent.push_back(edge);
			}
			
			_vertices[vertex] = adjacent;
		}
	}
	
	
	adjacent_t& operator[](vertex_t vertex)
	{
		return _vertices.at(vertex);
	}
	
	const adjacent_t& operator[](vertex_t vertex) const
	{
		return _vertices.at(vertex);
	}
	
	
	std::size_t vertex_number() const
	{
		return _vertices.size();
	}
	
private:
	
	std::vector<adjacent_t> _vertices;
};

int find_max_cost(const Graph& graph,
				  Graph::vertex_t vertex,
				  std::vector<int>& cache)
{
	if (cache[vertex]) return cache[vertex];
	
	int maximum = 0;
	
	for (const auto& edge : graph[vertex])
	{
		int cost = edge.cost;
		
		cost += find_max_cost(graph, edge.vertex, cache);
		
		if (cost > maximum) maximum = cost;
	}
	
	cache[vertex] = maximum;
	
	return maximum;
}

int max_cost(const std::vector<std::string>& components,
			 const std::vector<std::string>& costs)
{
	Graph graph(components, costs);
	
	int maximum = 0;
	
	std::vector<int> cache(components.size(), 0);
	
	for (Graph::vertex_t i = 0; i < graph.vertex_number(); ++i)
	{
		auto cost = find_max_cost(graph, i, cache);
		
		if (cost > maximum) maximum = cost;
	}
	
	return maximum;
}

#endif /* CIRCUITS_HPP */