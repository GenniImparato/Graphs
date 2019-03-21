//
// Created by Genni on 2/22/2019.
//

#include <limits>
#include <set>
#include <queue>
#include <iostream>
#include <vector>
#include <Dijkstra.h>
#include <algorithm>
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
        distances.push_back(numeric_limits<int>::max());
        fromNode.push_back(nullptr);
        analyzedNodes.push_back(false);
    }

    //comparator to find min in queue
    class comparator
    {
        public:
            bool operator ()(pair<int, int>&p1 ,pair<int, int>&p2)
            {
                return p1.second > p2.second;
            }
    };

    //queue of pairs <node id, distance>
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparator> q;

    //sets starting node to 0 distance
    distances[startNode->getId()] = 0;

    //push start node as first element of the queue
    q.push(make_pair(startNode->getId(), distances[startNode->getId()]));

    while(!q.empty())
    {
        //pop node with min distance from queue
        pair<int, int> currentPair = q.top();
        q.pop();

        int currNodeId = currentPair.first;
        int currDist = currentPair.second;

        //curr node already visited
        if(analyzedNodes[currNodeId])
            continue;

        analyzedNodes[currNodeId] = true;

        vector<Edge*> edgesFromMinNode = graph->getEdgesFromNode(currNodeId);

        for (int j = 0; j < edgesFromMinNode.size(); j++)
        {
            int node2 = edgesFromMinNode[j]->getNode2()->getId();

            if (!analyzedNodes[node2] &&
                    currDist + edgesFromMinNode[j]->getWeight() <= distances[node2])
            {
                distances[node2] = currDist + edgesFromMinNode[j]->getWeight();
                fromNode[node2] = graph->getNodes()[currNodeId];

                //push this node to the queue
                q.push(make_pair(node2, distances[node2]));
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


int Dijkstra::getCostTo(int node)
{
    int cost = 0;

    vector<Edge*> edges = getEdgesOnShortestPathTo(node);
    if(edges.empty())
        return numeric_limits<int>::infinity();

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

