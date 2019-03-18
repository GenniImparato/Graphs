#include <limits>
#include <set>
#include <algorithm>
#include <iostream>
#include <DijkstraConstrained.h>

#include "Graphs.h"

using namespace std;
using namespace Graphs;

DijkstraConstrained::DijkstraConstrained(Graph *graph, int startNode, float maxCost) : Algorithm(graph)
{
  this->maxCost = maxCost;
  execute(startNode);

}

bool DijkstraConstrained::execute(int startNode)
{
  if(startNode < 0  || startNode >= graph->getNodesCount())
    return false;

  this->startNode = graph->getNodes()[startNode];
  return execute();
}

bool DijkstraConstrained::execute(int startNode, float maxCost)
{
  if(startNode < 0  || startNode >= graph->getNodesCount())
    return false;
  this->maxCost = maxCost;

  this->startNode = graph->getNodes()[startNode];
  return execute();
}

bool DijkstraConstrained::execute()
{
  vector<bool>    analyzedNodes;

  distances.clear();
  fromNode.clear();
  reachedNodes.clear();

  for(int i=0; i<graph->getNodesCount(); i++)
    {
      distances.push_back(numeric_limits<float>::infinity());
      fromNode.push_back(nullptr);
      analyzedNodes.push_back(false);
    }

  //sets starting node to 0 distance
  distances[startNode->getId()] = 0;
  bool  stopExecution = false;
  for (int i=0; i< graph->getNodes().size() && !stopExecution; i++)
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

	  if (getCostTo(minDistIndex) >= maxCost )
	    stopExecution = true;
	  else
	    {
	      for (int j = 0; j < edgesFromMinNode.size(); j++)
		{
		  if (!analyzedNodes[edgesFromMinNode[j]->getNode2()->getId()] &&
		      distances[minDistIndex] + edgesFromMinNode[j]->getWeight() <= distances[edgesFromMinNode[j]->getNode2()->getId()]
		      && distances[minDistIndex] + edgesFromMinNode[j]->getWeight() <= maxCost)
		    {
		      distances[edgesFromMinNode[j]->getNode2()->getId()] = distances[minDistIndex] + edgesFromMinNode[j]->getWeight();
		      fromNode[edgesFromMinNode[j]->getNode2()->getId()] = graph->getNodes()[minDistIndex];
		      if(!isReached(edgesFromMinNode[j]->getNode2()->getId()))
			reachedNodes.push_back(edgesFromMinNode[j]->getNode2());
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

  return ret;
}


float DijkstraConstrained::getCostTo(int node)
{
  if (!isReached(node))
    return numeric_limits<float>::lowest();
  float cost;

  for(auto edge : getEdgesOnShortestPathTo(node))
    cost += edge->getWeight();

  return cost;
}

vector<Edge*> DijkstraConstrained::getEdgesOnShortestPathTo(int node)
{
  vector<Edge*> ret;
  vector<Node*> path = getNodesOnShortestPathTo(node);

  for(int i=0; i<path.size()-1; i++)
    ret.push_back(graph->getEdge(path[i]->getId(), path[i+1]->getId()));

  return ret;
}

