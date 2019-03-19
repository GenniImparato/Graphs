//
// Created by Genni on 2/22/2019.
//

#include <limits>
#include <set>
#include <algorithm>
#include <iostream>
#include <Dijkstra.h>

#include "Graphs.h"

using namespace std;

Dijkstra::Dijkstra(Graph *graph, int startNode) : Algorithm(graph)
{
    execute(startNode);
}


bool Dijkstra::execute(int startNode)
{
    if(!graph->isNodeIdValid(startNode))
        return false;

    this->startNode = graph->getNodes()[startNode];
    return execute();
}

bool Dijkstra::execute()
{
    vector<bool>    analyzedNodes;

    distances.clear();
    fromNode.clear();

    for(int i=0; i<graph->getNodesCount(); i++)
    {
        distances.push_back(numeric_limits<float>::infinity());
        fromNode.push_back(nullptr);
        analyzedNodes.push_back(false);
    }

    //sets starting node to 0 distance
    distances[startNode->getId()] = 0;

    for(int i=0; i<graph->getNodes().size(); i++)
    {
        float minDist = numeric_limits<float>::infinity();
        int minDistIndex = 0;

        //find node with min distance
        for (int j = 0; j < graph->getNodesCount(); j++)
        {
            if (!analyzedNodes[j] && distances[j] <= minDist)
            {
                minDist = distances[j];
                minDistIndex = j;
            }
        }

        //removes the current node from to be visited nodes list
        analyzedNodes[minDistIndex] = true;

        vector<Edge*> edgesFromMinNode = graph->getEdgesFromNode(minDistIndex);

        for (int j = 0; j < edgesFromMinNode.size(); j++)
        {
            if (!analyzedNodes[edgesFromMinNode[j]->getNode2()->getId()] &&
                distances[minDistIndex] + edgesFromMinNode[j]->getWeight() <= distances[edgesFromMinNode[j]->getNode2()->getId()])
            {
                distances[edgesFromMinNode[j]->getNode2()->getId()] = distances[minDistIndex] + edgesFromMinNode[j]->getWeight();
                fromNode[edgesFromMinNode[j]->getNode2()->getId()] = graph->getNodes()[minDistIndex];
            }
        }
    }

    return true;
}

vector<Node*> Dijkstra::getNodesOnShortestPathTo(int node)
{
    if(!graph->isNodeIdValid(node))
        return vector<Node*>();

    Node *n = graph->getNodes()[node];

    vector<Node*> ret;

    //no path
    if(fromNode[n->getId()] == nullptr)
        return ret;

    while(n!=nullptr)
    {
        ret.push_back(n);
        n = fromNode[n->getId()];
    }

    reverse(ret.begin(), ret.end());

    if(ret[0]->getId() != startNode->getId())
        ret.clear();

    return ret;
}


float Dijkstra::getCostTo(int node)
{
    float cost = 0;

    vector<Edge*> edges = getEdgesOnShortestPathTo(node);
    if(edges.empty())
        return numeric_limits<float>::infinity();

    for(auto edge : edges)
        cost += edge->getWeight();

    return cost;
}

vector<Edge*> Dijkstra::getEdgesOnShortestPathTo(int node)
{
    vector<Edge*> ret;
    vector<Node*> path = getNodesOnShortestPathTo(node);

    if(path.empty())
       return ret;

    for(int i=0; i<path.size()-1; i++)
        ret.push_back(graph->getEdge(path[i]->getId(), path[i+1]->getId()));

    return ret;
}

