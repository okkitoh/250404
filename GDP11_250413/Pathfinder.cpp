
#include "Pathfinder.h"

#include <queue>
#include <unordered_map>

//
// Does not support Edge objects with negative costs
// Bellman-Ford algorithm is a better suit for that scenario
std::vector<Tile> PF_Dijkstra::FindPath(std::vector<std::list<Edge<Tile>>>& adjacencyList, int rows, int cols, Tile start, Tile end)
{
    // Instead of using x,y directly, simpler to hash them into a single number
    // which happens to coincide with the positive integer space [0, Inf)
    int startHash = start.hash(cols);
    int goalHash = end.hash(cols);
    // Holds tile indicies, to -> from.
    // Get shortest path by working backwards from last tile, where M[End] = Start
    // Path is unreachable if last tile M[End] does not exist -- M.find(End) == M.end()
    std::unordered_map<int, int> path;
    path[startHash] = -1;
    // Holds the next neighbors to visit. The queue is sorted by the travel cost to this neighbor.
    std::priority_queue<Edge<int>> tovisit;
    tovisit.push({ startHash, 0.0 });
    // Holds the accumulated travel cost from start. Tiles that are revisted from other paths may update with a lower cost.
    std::vector<double> visited;
    visited.resize(rows * cols, -1.0);
    visited[startHash] = 0;
    int iterationCount = 0;
    while (!tovisit.empty())
    {
        // Get value of the lowest cost neighbor to visit, i.e Edge { to: /hashedxy/, cost: /cost/ }
        Edge<int> current = tovisit.top();
        // Remove the top of the queue
        tovisit.pop();
        // Base case: trivial case when start == end. Goal found, no more work to be done
        if (current.to == goalHash)
            break;
        // This edge from the outside world uses a Tile object which is really a vec2 { x, y }
        for (Edge<Tile>& edge : adjacencyList[current.to])
        {
            // Convert outside Edge<Tile> to inside Edge<int> which uses format { to: /hashedxy/, cost: /cost/ }
            // this is an implementation quirk intentionally hidden from user.
            // the user should not need to worry about calculating all their indices before using this function
            // although the algorithm prefers it to run faster.
            Edge<int> neighbor = { edge.to.hash(cols), edge.cost };
            // (traveled amt) + (next step)
            double cost = visited[current.to] + neighbor.cost;
            // If neighbor has not been seen yet
            // If current cost is cheaper than some cost calculated in the past
            if (visited[neighbor.to] < 0 || cost < visited[neighbor.to])
            {
                // update with new cost
                visited[neighbor.to] = cost;
                // mark how to get to this neighbor
                path[neighbor.to] = current.to;
                // push into queue to be sorted so the next iteration can prioritze the cheapest neighbor
                tovisit.push(neighbor);
            }
        }
        iterationCount++;
    }
    printf("\nnum of iterations: %d\n", iterationCount);
    if (!path.count(goalHash))
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
        shortestPath.push_back(Tile{ walk % cols, walk / cols });
    }
    std::reverse(shortestPath.begin(), shortestPath.end());
    std::reverse(track.begin(), track.end());
    for (int i = 0; i < track.size(); ++i) {
        printf("%d ", track[i]);
    }
    printf("\n");
    return shortestPath;
}
// A* algorithm is nothing more than Dijkstra with a heuristic value.
// In normal people speak, this value is just another cost variable to guide and correct the path
std::vector<Tile> PF_AStar::FindPath(std::vector<std::list<Edge<Tile>>>& adjacencyList, int rows, int cols, Tile start, Tile end)
{
    std::unordered_map<int, double> visited = std::unordered_map<int, double>();

    std::priority_queue<Edge<int>> tovisit;
    Edge<int> current = { start.y * cols + start.x , 0.0 };
    tovisit.push(current);

    std::unordered_map<int, int> path;
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

        for (Edge<Tile>& edge : adjacencyList[current.to])
        {
            double cost = visited[current.to] + edge.cost;
            int next = edge.to.hash(cols);
            if (visited.find(next) == visited.end() || cost < visited[next])
            {
                visited[next] = cost;
                path[next] = current.to;
                // manhattan distance as the heuristic. As a taxi cab drives through manhattan, right angles only
                // the disadvantage is it does not know about impassable walls. it may get caught exploring crevices
                double heuristic = (std::abs(x - end.x) + std::abs(y - end.y));
                printf("%d -> %d, c: %f, h: %f, t: %f\n", current.to, next, cost, heuristic, cost + heuristic);
                tovisit.push(Edge<int> { next, cost + heuristic });
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

