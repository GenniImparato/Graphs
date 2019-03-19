//
// Created by Genni on 3/18/2019.
//

#include <iostream>
#include "Graphs.h"

using namespace std;
using namespace Graphs;

//examples with graphs

int main()
{
    Graph g;

    //add 1000 nodes
    while(g.addNode()<1000);

    //connects the nodes from 0 to 399 with weight=100
    for(int i=0; i<400; i++)
        g.addEdge(i, i+1, 100);

    //connects the nodes from 500 to 999 with weight=150
    for(int i=500; i<1000; i++)
        g.addEdge(i, i+1, 150);

    //print graph
    cout << "Graphs Test" << g << endl;

    //execute and print dijkstra algorithm form node 0 to 150
    Dijkstra d(&g, 0);

    for(auto node : d.getNodesOnShortestPathTo(150))
        cout << node->getId() << "-> ";
    cout << endl << endl;

    for(auto edge : d.getEdgesOnShortestPathTo(35))
        cout << edge->getWeight() << "-> ";
    cout << endl << endl;
}
