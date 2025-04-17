#ifndef CONCRETEASTAR_H
#define CONCRETEASTAR_H

#include <vector>
#include <list>

struct Tile {
	double x;
	double y;
};

struct Edge {
	Tile from;
	Tile to;
	double cost;
};

class ConcreteAStar {
private:
	std::vector<std::list<Edge>> adjacencyList;
public:
	ConcreteAStar(std::vector<std::list<Edge>>& edges);
};

#endif
