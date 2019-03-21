#include <limits>
#include <set>
#include <algorithm>
#include <iostream>
#include <DijkstraConstrained.h>
#include <queue>
#include "Graphs.h"

using namespace std;
using namespace Graphs;

DijkstraConstrained::DijkstraConstrained(Graph *graph, int startNode, int maxCost) : Algorithm(graph)
{
    this->maxCost = maxCost;
    execute(startNode);
}

bool DijkstraConstrained::execute(int startNode)
{
    if(!graph->isNodeIdValid(startNode))
        return false;

    this->startNode = graph->getNode(startNode);
    return execute();
}

bool DijkstraConstrained::execute(int startNode, int maxCost)
{
    if(!graph->isNodeIdValid(startNode))
    return false;
  this->maxCost = maxCost;

  this->startNode = graph->getNode(startNode);
  return execute();
}

bool DijkstraConstrained::execute()
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

    bool stopExecution = false;

    while(!q.empty() && !stopExecution)
    {
        //pop node with min distance from queue
        pair<int, int> currentPair = q.top();
        q.pop();

        int currNodeId = currentPair.first;
        int currDist = currentPair.second;


        if(currDist >= maxCost)
            stopExecution = true;
        else
        {
            //curr node already visited
            if (analyzedNodes[currNodeId])
                continue;

            analyzedNodes[currNodeId] = true;

            vector<Edge *> edgesFromMinNode = graph->getEdgesFromNode(currNodeId);

            for (int j = 0; j < edgesFromMinNode.size(); j++)
            {

                int node2 = edgesFromMinNode[j]->getNode2()->getId();

                if (!analyzedNodes[node2] &&
                    currDist + edgesFromMinNode[j]->getWeight() <= distances[node2])
                {
                    distances[node2] = currDist + edgesFromMinNode[j]->getWeight();
                    fromNode[node2] = graph->getNodes()[currNodeId];
                    if(!isReached(node2))
                        reachedNodes.push_back(edgesFromMinNode[j]->getNode2());

                    //push this node to the queue
                    q.push(make_pair(node2, distances[node2]));
                }
            }
        }
    }

    return true;
}

vector<Node*> DijkstraConstrained::getReachedNodes()
{
    return reachedNodes;
}

bool DijkstraConstrained::isReached(int node)
{
    for (auto n : reachedNodes)
    {
        if (n->getId() == node)
	    return true;
    }
    return false;
}

vector<Node*> DijkstraConstrained::getNodesOnShortestPathTo(int node)
{
    if(!graph->isNodeIdValid(node) || !isReached(node))
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


int DijkstraConstrained::getCostTo(int node)
{
    if (!isReached(node))
        return numeric_limits<int>::max();
    int cost;

    for(auto edge : getEdgesOnShortestPathTo(node))
        cost += edge->getWeight();

    return cost;
}

vector<Edge*> DijkstraConstrained::getEdgesOnShortestPathTo(int node)
{
    vector<Edge*> ret;
    vector<Node*> path = getNodesOnShortestPathTo(node);

    if(path.empty())
        return ret;

    for(int i=0; i<path.size()-1; i++)
        ret.push_back(graph->getEdge(path[i]->getId(), path[i+1]->getId()));

    return ret;
}

