#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <list>
#include <map>



struct Tile {
	int x;
	int y;

	inline bool operator==(const Tile& other) const {
		return (x == other.x && y == other.y);
	}
	inline int hash(int num_of_cols) {
		return y* num_of_cols + x;
	}
};

template <typename T>
struct Edge {
	T to;
	double cost;

	inline bool operator<(const Edge& other) const {
		return cost > other.cost;
	}
};



// Strategy Pattern
// Using polymorphism to choose which algorithm to execute at runtime
class PathFinder {
public:
	virtual std::vector<Tile> FindPath(std::vector<std::list<Edge<Tile>>>& adjacencyList, int rows, int cols, Tile start, Tile end) = 0; // = 0, pure virtual
};



// Derived Class : A* algorithm
class PF_AStar : public PathFinder {
public:
	~PF_AStar() = default;
	std::vector<Tile> FindPath(std::vector<std::list<Edge<Tile>>>& adjacencyList, int rows, int cols, Tile start, Tile end) override;
};

// Derived Class : Djikstra algorithm
class PF_Dijkstra : public PathFinder {
public:
	~PF_Dijkstra() = default;
	std::vector<Tile> FindPath(std::vector<std::list<Edge<Tile>>>& adjacencyList, int rows, int cols, Tile start, Tile end) override;
};

#endif
