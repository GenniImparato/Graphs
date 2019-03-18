//
// Created by Genni on 2/22/2019.
//

#include "Graphs.h"

Graphs::Edge::Edge(Graphs::Node *n1, Graphs::Node *n2, float weight, void* valPtr)
{
    this->n1 = n1;
    this->n2 = n2;
    this->weight = weight;
    this->valPtr = valPtr;
}

Graphs::Node *Graphs::Edge::getNode1()
{
    return n1;
}

Graphs::Node *Graphs::Edge::getNode2()
{
    return n2;
}

float Graphs::Edge::getWeight()
{
    return weight;
}

void *Graphs::Edge::getValPtr()
{
    return valPtr;
}

