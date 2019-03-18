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

    //creates edges
    edgesMatrix.resize(graph.getNodesCount());
    for(int i=0; i<edgesMatrix.size(); i++)
        edgesMatrix[i].resize(graph.getNodesCount());

    for(int i=0; i<graph.getNodesCount(); i++)
    {
        for(int j=0; j<graph.getNodesCount(); j++)
        {
            if(graph.edgesMatrix[i][j] != nullptr)
                edgesMatrix[i][j] = new Edge(   nodes[graph.edgesMatrix[i][j]->getNode1()->getId()],
                                                nodes[graph.edgesMatrix[i][j]->getNode2()->getId()],
                                                graph.edgesMatrix[i][j]->getWeight(),
                                                graph.edgesMatrix[i][j]->getValPtr());
        }
    }
}


Graph::~Graph()
{
    //dealloc mem used for nodes
    for(auto node : nodes)
        delete node;

    //dealloc mem used for edges
    for(auto col : edgesMatrix)
    {
        for(auto edge : col)
            if(edge != nullptr)
                delete edge;

        col.clear();
    }
    edgesMatrix.clear();
}

void Graph::incrementEdgesMatrixSize()
{
    vector<Edge*>   lastCol;
    lastCol.resize(edgesMatrix.size()+1);

    //adds one more col to the matrix
    edgesMatrix.push_back(lastCol);

    //add one more row to the matrix
    for(int i=0; i<edgesMatrix.size()-1; i++)
        edgesMatrix[i].push_back(nullptr);
}


int Graph::addNode()
{
    return addNode(nullptr);
}

int Graph::addNode(void *valPtr)
{
    nodes.push_back(new Node(currNode, valPtr));
    incrementEdgesMatrixSize();

    currNode++;

    return currNode-1;
}

bool Graph::addEdge(int node1, int node2, float weight)
{
    return addEdge(node1, node2, weight, nullptr);
}

bool Graph::addEdge(int node1, int node2, float weight, void *valPtr)
{
    //check if node ids are in correct range
    if(!isNodeIdValid(node1) || !isNodeIdValid(node2))
        return false;

    Node* n1 = nodes[node1];
    Node* n2 = nodes[node2];

    if(n1== nullptr || n2==nullptr)
        return false;

    int id = n1->getId();

    if(edgesMatrix[node1][node2] != nullptr)
        delete edgesMatrix[node1][node2];

    edgesMatrix[node1][node2] = new Edge(n1, n2, weight, valPtr);

    return true;
}


void Graph::clearEdges()
{
    for(auto col : edgesMatrix)
    {
        for(auto edge : col)
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

    return edgesMatrix[node1][node2];
}

vector<Node*> Graph::getAdjacentNodes(int node)
{
    if(!isNodeIdValid(node))
        return vector<Node*>();

    vector<Node*>   ret;

    for(int i=0; i<getNodesCount(); i++)
        if(edgesMatrix[node][i] != nullptr)
            ret.push_back(edgesMatrix[node][i]->getNode2());

    return ret;
}

vector<Edge *> Graph::getEdgesFromNode(int node)
{
    if(!isNodeIdValid(node))
        return vector<Edge*>();

    vector<Edge*>   ret;

    for(int i=0; i<getNodesCount(); i++)
        if(edgesMatrix[node][i] != nullptr)
            ret.push_back(edgesMatrix[node][i]);

    return ret;
}

bool Graph::isNodeIdValid(int node)
{
    return node >= 0 && node < getNodesCount();
}

