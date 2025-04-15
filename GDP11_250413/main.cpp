
#include <iostream>
#include <vector>
#include <map>

#include "MyGraph.h"


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
    AMGraph::AddEdge(3, 4);
    AMGraph::AddEdge(4, 5);
    AMGraph::AddEdge(5, 9);
    // Dead-end
    AMGraph::AddEdge(3, 6);
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
        {8, 9}
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
}
