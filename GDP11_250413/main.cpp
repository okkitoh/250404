
#include <iostream>
#include <vector>
#include <map>

#include "MyGraph.h"
#include "Pathfinder.h"


int main()
{
    //std::mt19937 Generator;
    //std::uniform_int_distribution<> Distribution;

    AMGraph::Create(10);
    AMGraph::AddEdge(1, 2);
    AMGraph::AddEdge(2, 3);
    AMGraph::AddEdge(3, 0);
    AMGraph::AddEdge(0, 1);

    AMGraph::AddEdge(5, 4);
    AMGraph::AddEdge(5, 6);
    AMGraph::AddEdge(6, 9);

    AMGraph::Print();
    std::vector<int> res = AMGraph::Explore(1);

    printf("\n\nAn Exploration of Space: \n");
    std::vector<std::vector<int>> subgraphs = AMGraph::ExploreAll();
    for (int i = 0; i < subgraphs.size(); ++i)
    {
        printf("subgraph %-2d: ", i + 1);
        for (int j = 0; j < subgraphs[i].size(); ++j)
        {
            printf("%-2d ", subgraphs[i][j]);
        }

        printf("\n");
    }

    AMGraph::Create(10);
    // Main path
    AMGraph::AddEdge(1, 2);
    AMGraph::AddEdge(2, 3);
    AMGraph::AddEdge(3, 4, 9);
    AMGraph::AddEdge(4, 5);
    AMGraph::AddEdge(5, 9);
    // Dead-end
    AMGraph::AddEdge(3, 6, 1);
    AMGraph::AddEdge(6, 7);
    AMGraph::AddEdge(7, 8);


    printf("\n\nCreating a spanning tree graph same same\n");
    printf("0   1 - 2 - 3 - 4 - 5 - 9\n");
    printf("             \\_ 6 - 7 - 8\n\n");
    AMGraph::Print();

    std::map<int, int> testdriver = {
        {9, 7},
        {0, 0},
        {6, 0},
        {1, 7}
    };
    std::map<int, int>::iterator iter = testdriver.begin();
    while (iter != testdriver.end())
    {
        printf("\nFinding a path from %d to %d:\n", iter->first, iter->second);
        std::vector<int> path = AMGraph::FindPath(iter->first, iter->second);
        if (path.empty()) {
            printf("!!No Path Found\n");
        }
        else
        {
            for (int i = 0; i < path.size(); ++i)
            {
                printf("%d ", path[i]);
            }
            printf("\n");
        }
        iter++;
    }

    
    printf("\n\nCreating a cyclic graph with weights\n");
    printf("0 --(2)-- 1 ----------(9)------      \n");
    printf("           \\                   \\   \n");
    printf("           (1)                  \\   \n");
    printf("             \\                   \\ \n");
    printf("              2 --(5)-- 3 --(4)-- 4  \n");
    printf("              |         |         |  \n");
    printf("             (1)       (1)      (10) \n");
    printf("              |         |         |  \n");
    printf("              5 --(1)-- 6 --(9)-- 7  \n");
    AMGraph::Create(10);
    // Main path
    AMGraph::AddEdge(0,1, 2);
        AMGraph::AddEdge(1,4, 9);
        
        AMGraph::AddEdge(1,2, 1);
        AMGraph::AddEdge(2,3, 5);
        AMGraph::AddEdge(3,4, 4);

        AMGraph::AddEdge(2,5, 1);
        AMGraph::AddEdge(5,6, 1);
        AMGraph::AddEdge(6,3, 1);
        AMGraph::AddEdge(6,7, 9);
        AMGraph::AddEdge(7,4, 10);
    AMGraph::Print();


    testdriver = {
        {0, 4},
        {3, 9}
    };
    iter = testdriver.begin();
    while (iter != testdriver.end())
    {
        printf("\nFinding a path from %d to %d:\n", iter->first, iter->second);
        std::vector<int> path = AMGraph::Dijkstra(iter->first, iter->second);
        if (path.empty()) {
            printf("!!No Path Found\n");
        }
        else
        {
            for (int i = 0; i < path.size(); ++i)
            {
                printf("%d ", path[i]);
            }
            printf("\n");
        }
        iter++;
    }


    printf("\n\nCreating a tile based grid with obstacles\n");
    // Assume origin is at top left like raylib
    const int rows = 6; // row is to y
    const int cols = 6; // col is to x
    
    const char WALL = '@';
    const char FLOOR = '.';

    // This is an undirected graph
    std::vector<std::vector<char>> TileGraph = 
    {
        { '.', '@', '@', '@', '.', '.' },
        { '.', '.', '.', '@', '.', '.' },
        { '.', '.', '.', '@', '.', '.' },
        { '.', '@', '@', '@', '.', '.' },
        { '.', '.', '.', '.', '.', '.' },
        { '.', '.', '.', '.', '.', '.' },
    };

    // Map Bake Stage
    // ---------------------------------------------------------------------------------
    // Create an edge list representation from graph an adjacency list.
    // Array of arrays holding a list of edges to neighbors.
    // [ 0 ] -> [1, 2]           0
    // [ 1 ] -> [0, 2]          / \
    // [ 2 ] -> [0, 1]         2 - 1
    // It is more performant and saves alot of space vs an adjacency matrix
    // By using a map to hold the list we're speeding up look up times. If we needed
    // position 283 in a list, the search would have to start from 0 and iterate to 283.
    //
    // A map is a key-value pair and lookups are 0(log n) vs O(n) because 
    // std::map uses a self balancing tree (red-black tree) for look ups
    // Like 20 questions, a binary tree can find an answer in 20 questions or less.
    // It has a logarithmic upper bound no matter how large the search space.

    // I'm dumb, use 0(1)
    //std::map<int, std::list<Edge>> driver;

    std::vector<std::list<Edge>> adjacencyList = std::vector<std::list<Edge>>();
    adjacencyList.resize(rows * cols);
    std::string header = "\n   +";
    printf("\n   |");
    for (int hr = 0; hr < cols; ++hr)
    {
        printf("%3d", hr);
        header += "---";
    }
    std::cout << header << " x\n";
    for (int r = 0; r < rows; ++r)
    {
        printf("%2d | ", r);
        for (int c = 0; c < cols; ++c)
        {
            printf("%2c ", TileGraph[r][c]);
            // Goal for scope: for every tile, check each neighbor and see if path exists
            if (TileGraph[r][c] == WALL) continue;

            // need to map (x, y) aka (c, r) to a linear space like an array to use as a map key
            // that is unique for each tile. this is called hashing
            int index = r * cols + c;

            for (int u = -1; u < 2; ++u)
            {
                for (int v = -1; v < 2; ++v)
                {
                    if (u == 0 && v == 0)
                        continue;
                    int nr = r + u;
                    int nc = c + v;
                    if ((nr < 0 || nr >= rows) || (nc < 0 || nc >= cols))
                        continue;
                    if (TileGraph[nr][nc] == WALL)
                        continue;

                    double cost = abs(u) + abs(v) == 2 ? 1.414 : 1.0;
                    Edge edge = { {c, r}, {nc, nr}, cost };
                    adjacencyList[index].push_back(edge);
                }
            }
        }
        printf("\n");
    }
    printf("   y\n");

    PathFinder *pathfinder = new PF_AStar();
    pathfinder->FindPath(adjacencyList, rows, cols, {0, 1}, {4, 1});
    delete pathfinder;
    pathfinder = nullptr;
}
