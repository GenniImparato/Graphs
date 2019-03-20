//
// Created by Genni on 2/22/2019.
//

#ifndef GRAPHS_EXAMPLES_EDGE_H
#define GRAPHS_EXAMPLES_EDGE_H

#include "Node.h"

namespace Graphs
{
    class Edge
    {
        protected:
          Node          *n1;
          Node          *n2;
          int           weight;
          void          *valPtr;

        public:
          Edge(Node *n1, Node *n2, int weight, void* valPtr);

          Node*     getNode1();
          Node*     getNode2();
          int       getWeight();
          void*     getValPtr();
    };
}


#endif //GRAPHS_EXAMPLES_EDGE_H
