//
// Created by Genni on 2/21/2019.
//

#include <iostream>
#include "Graphs.h"

using namespace Graphs;
using namespace std;

Graph::Graph()
{

}

//copy constructor
Graph::Graph(Graph &graph)
{
    //copy all nodes
    for(int i=0; i<graph.getNodes().size(); i++)
        this->nodes.push_back(new Node(*graph.getNodes()[i]));

}


Graph::~Graph()
{
    //dealloc mem used for nodes
    for(auto node : nodes)
        delete node;

    //dealloc mem used for edges
    for(auto list : edgeLists)
    {
        for(auto edge : list)
            if(edge != nullptr)
                delete edge;

        list.clear();
    }
    edgeLists.clear();
}

void Graph::incrementEdgesSize()
{
    vector<Edge*>   newList;
    edgeLists.push_back(newList);
}


int Graph::addNode()
{
    return addNode(nullptr);
}

int Graph::addNode(void *valPtr)
{
    nodes.push_back(new Node(currNode, valPtr));
    incrementEdgesSize();

    currNode++;

    return currNode-1;
}

bool Graph::addEdge(int node1, int node2, int weight)
{
    return addEdge(node1, node2, weight, nullptr);
}

bool Graph::addEdge(int node1, int node2, int weight, void *valPtr)
{
    //check if node ids are in correct range
    if(!isNodeIdValid(node1) || !isNodeIdValid(node2))
        return false;

    Node* n1 = nodes[node1];
    Node* n2 = nodes[node2];

    if(n1== nullptr || n2==nullptr)
        return false;

    int id = n1->getId();

    edgeLists[node1].push_back(new Edge(n1, n2, weight, valPtr));
    currEdge++;

    return true;
}


void Graph::clearEdges()
{
    for(auto list : edgeLists)
    {
        for(auto edge : list)
            if(edge != nullptr)
                delete edge;
    }
}



ostream &Graphs::operator<<(ostream &os, Graph &graph)
{
    for(int i=0; i<graph.getNodesCount(); i++)
    {
        os << "[" << graph.getNodes()[i]->getId() << "] -> ";

        vector<Edge*> edges = graph.getEdgesFromNode(i);

        for(auto edge : edges)
            os << edge->getNode2()->getId() << "(" << edge->getWeight() << ") ";

        os << endl;
    }

    return os;
}

Edge* Graph::getEdge(int node1, int node2)
{
    //check if node ids are in correct range
    if(!isNodeIdValid(node1) || !isNodeIdValid(node2))
        return nullptr;

    for(auto edge : edgeLists[node1])
        if(edge->getNode2()->getId() == node2)
            return edge;

    return nullptr;
}

vector<Node*> Graph::getAdjacentNodes(int node)
{
    if(!isNodeIdValid(node))
        return vector<Node*>();

    vector<Node*>   ret;

    for(auto edge : edgeLists[node])
        ret.push_back(edge->getNode2());

    return ret;
}

vector<Edge *> Graph::getEdgesFromNode(int node)
{
    if(!isNodeIdValid(node))
        return vector<Edge*>();

    vector<Edge*>   ret;

    return edgeLists[node];
}

bool Graph::isNodeIdValid(int node)
{
    return node >= 0 && node < getNodesCount();
}

