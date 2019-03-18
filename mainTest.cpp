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
    DijkstraConstrained d(&g, 0, 1000);

    vector<Node*> reachedNodes = d.getReachedNodes();

    cout << "Reached nodes from 0 with maximum cost of 1000: ";
    for (auto node: reachedNodes)
      {
	cout << node->getId() << ", ";
      }
    cout << endl;
    
    vector<Node*>   path = d.getNodesOnShortestPathTo(10);

    
    cout << "Shortest path (0, 10) = ";
    for(auto node : path)
        cout << node->getId() << "-> ";
    cout << endl << endl;

    path = d.getNodesOnShortestPathTo(150);

    
    cout << "Shortest path (0, 150) = ";
    for(auto node : path)
        cout << node->getId() << "-> ";
    cout << endl << endl;
    
    //creates a better path from 0 to 150
    g.addEdge(0, 30, 50);
    g.addEdge(30, 150, 75);

    //execute dijkstra again, now the best path given should be 0-> 30-> 150
    d.execute(0);
    path = d.getNodesOnShortestPathTo(150);

    cout << "Shortest path (0, 150) = ";
    for(auto node : path)
        cout << node->getId() << "-> ";
    cout << endl;

    //print edges on shorter path
    for(auto edge : d.getEdgesOnShortestPathTo(150))
        cout << "edge(" << edge->getNode1()->getId()
            << ", " << edge->getNode2()->getId() << ") = "
            << edge->getWeight() << " ";
    cout << endl;

    //print path cost
    cout << d.getCostTo(150) << endl << endl;

    //tries to find a path between unconnected nodes
    d.execute(150);
    path = d.getNodesOnShortestPathTo(800);

    cout << "Shortest path (150, 800) = ";
    for(auto node : path)
        cout << node->getId() << "-> ";
    cout << endl;

}
