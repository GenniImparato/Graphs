//
// Created by Genni on 2/22/2019.
//

#ifndef GRAPHS_EXAMPLES_ALGORITHM_H
#define GRAPHS_EXAMPLES_ALGORITHM_H

#include "Graph.h"

namespace Graphs
{
    class Algorithm
    {
        protected:
          Graph             *graph;

        public:
          explicit Algorithm(Graph *graph)          {this->graph = graph;};

          virtual bool execute()                    {return false;};
    };

}


#endif //GRAPHS_EXAMPLES_ALGORITHM_H
