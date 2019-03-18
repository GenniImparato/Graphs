#ifndef GRAPHS_GRAPH
#define GRAPHS_GRAPH

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <string>
#include <ostream>

using namespace std;

namespace Graphs
{
    class EdgeList;

    class Graph
    {
        private:
          vector<Node*>             nodes;
          vector<vector<Edge*>>     edgesMatrix;

          int                       currNode = 0;

          void                      incrementEdgesMatrixSize();

        public:
          Graph();
          Graph(Graph& graph);
          ~Graph();

          int               addNode();
          int               addNode(void* valPtr);
          bool              addEdge(int node1, int node2, float weight);
          bool              addEdge(int node1, int node2, float weight, void* valPtr);

          void              clearEdges();

          bool              isNodeIdValid(int node);
          int               getNodesCount()                 {return nodes.size();};
          vector<Node*>     getNodes()                      {return nodes;};
          vector<Node*>     getAdjacentNodes(int node);
          vector<Edge*>     getEdgesFromNode(int node);
          Edge*             getEdge(int node1, int node2);

          friend ostream &operator<<(ostream &os, Graph &graph);
    };
}

#endif
