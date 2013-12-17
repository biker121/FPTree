//
//  NodeLL.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include <iostream>
#include "Data.hpp"
#include "NodeLL.hpp"

//------------------Constructor/Destructor---------------------
NodeLL::NodeLL(Data *data, NodeLL *prev, NodeLL *next){
    this->data = data;
    this->prev = prev;
    this->next = next;
}
NodeLL::~NodeLL(){
    delete(data);
    this->data = NULL;
    this->prev = NULL;
    this->next = NULL;
}//------------------------------------------------------------

void NodeLL::print(){
    if (data != NULL){
        data->print();
    }
}

//************** GETTERS ***********************
Data* NodeLL::getData()
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

//************** SETTERS ***********************
void NodeLL::setData(Data *data)
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