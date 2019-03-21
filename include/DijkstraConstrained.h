//
// Created by Genni on 2/22/2019.
//

#ifndef GRAPHS_EXAMPLES_DIJKSTRA_CONSTRAINED_H
#define GRAPHS_EXAMPLES_DIJKSTRA_CONSTRAINED_H

#include "Node.h"
#include "Edge.h"
#include "Algorithm.h"
#include <vector>

using namespace std;

namespace Graphs
{
  
  class DijkstraConstrained : Algorithm
    {
        private:
            Node                *startNode;
	        float               maxCost;

            vector<int>         distances;
            vector<Node*>       fromNode;
	        vector<Node*>       reachedNodes;

        public:
            DijkstraConstrained(Graph *graph, int startNode, int maxCost);

            bool                execute() override;
            bool                execute(int startNode);
	        bool                execute(int startNode, int maxCost);

            vector<Node*>       getNodesOnShortestPathTo(int node);
	        vector<Node*>       getReachedNodes();
	        bool                isReached(int node);
            vector<Edge*>       getEdgesOnShortestPathTo(int node);
            int                 getCostTo(int node);
    };

}


#endif //GRAPHS_EXAMPLES_DIJKSTRA_CONSTRAINED_H
