
#include "MyGraph.h"
#include <queue>
#include <map>

namespace AMGraph
{
    char **adjacencyMatrix = nullptr;
    int NUMOFVERTS = 0;
}


void AMGraph::Create(int num_of_vertices)
{
    if (adjacencyMatrix != nullptr)
    {
        for (int row = 0; row < NUMOFVERTS; ++row)
        {
            delete [] adjacencyMatrix[row];
        }
        delete [] adjacencyMatrix;
    }

    NUMOFVERTS = num_of_vertices;
    // Dynamically allocate | V x V | grid of characters
    adjacencyMatrix = new char*[NUMOFVERTS];
    for (int row = 0; row < NUMOFVERTS; ++row)
    {
        adjacencyMatrix[row] = new char[NUMOFVERTS];
        // This is the long hand way. 3rd arg expects # of bytes, char type is 1 byte. 0-254
        // Also why many old online games put a cap of 255 [null, 255) Faster to send 1 byte
        memset(adjacencyMatrix[row], 0, sizeof(char) * NUMOFVERTS);
    }
}
void AMGraph::AddEdge(int start, int end)
{
    AMGraph::AddEdge(start, end, 1);
}
void AMGraph::AddEdge(int start, int end, int weight)
{
    // Marking edges on the matrix.
    // rows (going downward) are start vertices
    // columns (going across) are end verties
    // matrix[row][col] 0 means no edge
    //                  1 means has edge
    // Edges are symmetrical in an undirected graph
    adjacencyMatrix[start][end] = weight;
    adjacencyMatrix[end][start] = weight;
}
void AMGraph::Print()
{
    printf("Adjacency Matrix\n");
    printf("    |");
    for (int h = 0; h < NUMOFVERTS; ++h)
    {
        printf("%3d", h);
    }
    printf("\n----+------------------------------\n");
    for (int r = 0; r < NUMOFVERTS; ++r)
    {
        printf("%3d |", r);
        for (int c = 0; c < NUMOFVERTS; ++c)
        {
            printf("%3d", adjacencyMatrix[r][c]);
        }
        printf("\n");
    }
}
// Running a depth first search. Useful in understanding the characteristics of a graph
// How many subgraphs?
// Back edges and cyclic vs acyclic nature
std::vector<int> AMGraph::Explore(int start)
{
    std::vector<int> visited = std::vector<int>();
    visited.resize(NUMOFVERTS);

    std::vector<int> tovisit = std::vector<int>();
    tovisit.push_back(start);
    // This is the iterative version of explore and is much more lighter weight (memory-wise)
    // than the recursive version that eats up stack memory.
    while (!tovisit.empty())
    {
        int vertex = tovisit.back();
        visited[vertex] = 1;
        tovisit.pop_back();
        // Poor Runtime: O(V * V)
        // need to look at every column of every row to find if edge exists
        for (int column = 0; column < NUMOFVERTS; ++column)
        {
            // add to the stack (tovisit) neighbors that have not been visited:
            // we have not visited this vertex
            // edges exists between our vertex and another vertex
            if (!visited[column] && adjacencyMatrix[vertex][column] == 1)
            {
                tovisit.push_back(column);
            }
        }
    }

    return visited;
}
std::vector<std::vector<int>> AMGraph::ExploreAll()
{
    std::vector<std::vector<int>> subgraphs = std::vector<std::vector<int>>();
    subgraphs.resize(NUMOFVERTS);
    int connectedComponentIndex = 0;
    // wtf add 1 to appease the compiler gods. they want their '\0'
    char* visited = new char[NUMOFVERTS+1];
    memset(visited, 0, NUMOFVERTS);

    for (int i = 0; i < NUMOFVERTS; ++i)
    {
        if (visited[i] == 1)
        {
            continue;
        }

        int vertex = i;
        std::vector<int> explored = Explore(vertex);
        subgraphs[connectedComponentIndex] = explored;
        connectedComponentIndex++;
        for (int j = 0; j < explored.size(); ++j)
        {
            if (explored[j] == 1)
            {
                visited[j] = 1;
            }
        }
    }
    delete[] visited;
    visited = nullptr; // good practice to null out pointers immediately after delete or could have wild pointers
    subgraphs.resize(connectedComponentIndex);
    return subgraphs;
}
// Running a breadth first search
// Useful in finding shortest path but exponentially expensive with size and density requirement
// Flow field generation, water takes the path of least resistance. tower defense game
// If only seeking shortest path, there are better heuristic systems
// Djikstra
// A*
std::vector<int> AMGraph::FindPath(int start, int end)
{
    std::vector<int> visited = std::vector<int>();
    visited.resize(NUMOFVERTS);
    
    // while DFS used a stack, BFS uses a queue to hold neighbors first in/first out. snek eat, snek poop
    std::queue<int> tovisit;
    tovisit.push(start);

    std::map<int, int> path;
    while (!tovisit.empty())
    {
        int vertex = tovisit.front();
        tovisit.pop();
        visited[vertex] = 1;
        // the search for neighbors
        for (int column = 0; column < NUMOFVERTS; ++column)
        {
            if (!visited[column] && adjacencyMatrix[vertex][column] >= 1)
            {
                path[column] = vertex;
                if (column == end)
                {
                    tovisit = std::queue<int>();
                    break;
                }
                tovisit.push(column);
            }
        }
    }
    visited.clear();

    // solve backwards following distance field aka flow map
    int next = end;
    while(next != start && path.find(next) != path.end())
    {
        visited.push_back(next);
        next = path[next];
    }
    if (next == start)
    {
        visited.push_back(next);
    }
    else
    {
        visited.clear();
    }
    std::reverse(visited.begin(), visited.end());
    return visited;
}
std::vector<int> AMGraph::Dijkstra(int start, int end)
{
    // djikstra requires non-negative edge weights from which it prioritizes
    // least resistance. when all weights are 1, you have a BFS
    std::priority_queue<WeightedEdge<int, int>> tovisit; // priority queue, sorts in ascending, small to large
    tovisit.push({start, 0});

    std::map<int, int> path;
    path[start] = -1;

    std::map<int, int> visited;
    visited[start] = 0;
    while (!tovisit.empty())
    {
        WeightedEdge<int, int> edge = tovisit.top();
        tovisit.pop();
        if (edge.to == end)
        {
            break;
        }
        else
        {
            for (int column = 0; column < NUMOFVERTS; ++column)
            {
                if (adjacencyMatrix[edge.to][column] >= 1)
                {
                    // (traveled amt) + (next step)
                    int cost = edge.weight + adjacencyMatrix[edge.to][column];
                    if (!visited.count(column) || cost < visited[column]) {
                        visited[column] = cost;
                        path[column] = edge.to;
                        tovisit.push({ column, cost });
                    }
                }
            }
        }
    }

    if (!path.count(end))
    {
        return std::vector<int>();
    }
    int current = end;
    std::vector<int> shortestPath;
    shortestPath.push_back(end);
    while (path[current] != -1)
    {
        current = path[current];
        shortestPath.push_back(current);
    }
    std::reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}
