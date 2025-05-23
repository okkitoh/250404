#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <vector>

template <typename T, typename U>
struct WeightedEdge
{
	T to;
	U weight;

	inline bool operator<(const WeightedEdge<T, U>& other) const {
		return weight > other.weight;
	}
	inline bool operator==(const WeightedEdge<T, U>& other) const {
		return (to == other.to);
	}
};



// Adjacency Matrix Graph
// Not particularly useful in the field due to poor runtime
// but good for conceptualizing and following along with pen and paper
namespace AMGraph
{
	void Create(int num_of_vertices);
	void AddEdge(int start, int end); // 0-based indexing
	void AddEdge(int start, int end, int weight);
	void Print();
	std::vector<int> Explore(int start);
	std::vector<std::vector<int>> ExploreAll();
	std::vector<int> FindPath(int start, int end);
	std::vector<int> Dijkstra(int start, int end);
}

#endif