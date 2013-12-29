#include <iostream>
#include "NodeLL.hpp"
#include "OrderedData.hpp"

//--------------------------------------------------------------------------//
//  NodeLL
//
//  A generic Node type for a linked list 
//--------------------------------------------------------------------------//

NodeLL::NodeLL(OrderedData *data, NodeLL *prev, NodeLL *next)
{
    this->data = data;
    this->prev = prev;
    this->next = next;
}

NodeLL::NodeLL(OrderedData* data)
{
    this->data = data;
    this->prev = NULL;
    this->next = NULL;
}

NodeLL::~NodeLL()
{
    delete(data);
    this->prev = NULL;
    this->next = NULL;
}

void NodeLL::print()
{
    if (data != NULL)
        data->print();
}

//----------------------GETTERS----------------------------//

OrderedData* NodeLL::getData()
{
    return this->data;
}

NodeLL* NodeLL::getPrev()
{
    return this->prev;
}

NodeLL* NodeLL::getNext()
{
    return this->next;
}

//----------------------SETTERS----------------------------//

void NodeLL::setData(OrderedData *data)
{
    this->data = data;
}

void NodeLL::setPrev(NodeLL *prev)
{
    this->prev = prev;
}

void NodeLL::setNext(NodeLL *next)
{
    this->next = next;
}