
#include <iostream>

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
}
