//
// Created by Genni on 2/22/2019.
//

#ifndef GRAPHS_EXAMPLES_EDGE_H
#define GRAPHS_EXAMPLES_EDGE_H

#include "Graphs.h"

namespace Graphs
{
    class Edge
    {
        protected:
          Node          *n1;
          Node          *n2;
          float         weight;
          void          *valPtr;

        public:
          Edge(Node *n1, Node *n2, float weight, void* valPtr);

          Node*     getNode1();
          Node*     getNode2();
          float     getWeight();
          void*     getValPtr();

          struct   AscendingWeight
          {
              bool operator()(Edge* l, Edge* r)
              {
                  return l->weight < r->weight;
              }
          };
    };
}


#endif //GRAPHS_EXAMPLES_EDGE_H
