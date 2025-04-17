
#include "Pathfinder.h"
#include "MyGraph.h"

#include <queue>

// A* algorithm is nothing more than Dijkstra with a heuristic value.
// In normal people speak, this value is just another cost variable to guide and correct the path
std::vector<Tile> PF_AStar::FindPath(std::map<int, std::list<Edge>>& adjacencyList, int rows, int cols, Tile start, Tile end)
{
    std::map<int, double> visited = std::map<int, double>();

    std::priority_queue<WeightedEdge<int, double>> tovisit;
    WeightedEdge<int, double> current = { start.y * cols + start.x , 0.0 };
    tovisit.push(current);

    std::map<int, int> path;
    path[start.hash(cols)] = -1;
    int iterationCount = 0;
    while (!tovisit.empty())
    {
        current = tovisit.top();
        tovisit.pop();
        int y = current.to / cols;
        int x = current.to % cols;

        if (Tile{ x, y } == end)
            break;

        for (Edge& edge : adjacencyList[current.to])
        {
            double cost = visited[current.to] + edge.cost;
            int next = edge.to.hash(cols);
            if (visited.find(next) == visited.end() || cost < visited[next])
            {
                visited[next] = cost;
                path[next] = current.to;
                // manhattan distance as the heuristic
                double heuristic = (std::abs(edge.from.x - end.x) + std::abs(edge.from.y - end.y));
                printf("%d -> %d, c: %f, h: %f, t: %f\n", current.to, next, cost, heuristic, cost + heuristic);
                tovisit.push(WeightedEdge<int, double> { next, cost + heuristic });
            }
        }
        iterationCount++;
    }
    printf("num of iterations: %d\n", iterationCount);
    if (!path.count(end.hash(cols)))
    {
        return std::vector<Tile>();
    }
    int walk = end.hash(cols);
    std::vector<Tile> shortestPath;
    std::vector<int> track;
    shortestPath.push_back(end);
    track.push_back(walk);
    while (path[walk] != -1)
    {
        walk = path[walk];
        track.push_back(walk);
        shortestPath.push_back(Tile { walk % cols, walk / cols });
    }
    std::reverse(shortestPath.begin(), shortestPath.end());
    std::reverse(track.begin(), track.end());
    for (int i = 0; i < track.size(); ++i) {
        printf("%d ", track[i]);
    }
    return shortestPath;
}
