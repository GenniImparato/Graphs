

#ifndef GRAPHS_NODE
#define GRAPHS_NODE

#include <string>

using namespace std;

namespace Graphs
{
    class Node
    {
        private:
          int       id;
          void*     valPtr;

        public:
          explicit  Node(int id, void* valPtr);
                    Node(Node &node);

           int      getId();
           void*    getValPtr();
    };
}

#endif