//
// Created by Genni on 2/22/2019.
//

#ifndef GRAPHS_EXAMPLES_DIJKSTRA_H
#define GRAPHS_EXAMPLES_DIJKSTRA_H

#include "Node.h"
#include "Algorithm.h"

using namespace Graphs;

namespace Graphs
{
    class Dijkstra : Algorithm
    {
        private:
          Node              *startNode;

          vector<int>       distances;
          vector<Node*>     fromNode;

        public:
          Dijkstra(Graph *graph, int startNode);

          bool              execute() override;
          bool              execute(int startNode);

          vector<Node*>     getNodesOnShortestPathTo(int node);
          vector<Edge*>     getEdgesOnShortestPathTo(int node);
          float             getCostTo(int node);
    };

}


#endif //GRAPHS_EXAMPLES_DIJKSTRA_H
