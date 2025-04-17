#include "ConcreteAStar.h"

#include <algorithm>

ConcreteAStar::ConcreteAStar(std::vector<std::list<Edge>>& edges)
{
	adjacencyList = std::move(edges);
}
