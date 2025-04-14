#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <vector>

// Adjacency Matrix Graph
// Not particularly useful in the field due to poor runtime
// but good for conceptualizing and following along with pen and paper
namespace AMGraph
{
	void Create(int num_of_vertices);
	void AddEdge(int start, int end); // 0-based indexing
	void Print();
	std::vector<int> Explore(int start);
	std::vector<std::vector<int>> ExploreAll();
	std::vector<int> FindPath(int start, int end);
}

namespace LLGraph
{
	
}


#endif