//
// Created by Genni on 2/21/2019.
//

#include "Graphs.h"

using namespace Graphs;


Node::Node(Node &node)
{
    this->id = node.id;
    this->valPtr = node.valPtr;
}


Node::Node(int id, void* valPtr)
{
    this->id = id;
    this-> valPtr = valPtr;
}


int Node::getId()
{
    return id;
}

void* Node::getValPtr()
{
    return valPtr;
}



