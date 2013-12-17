//
//  DOrderedList.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "DLinkedList.hpp"
#include "DOrderedList.hpp"

#include "Data.hpp"
#include "OrderedData.hpp"
#include "NodeLL.hpp"

//------------------Constructor/Destructor---------------------
DOrderedList::DOrderedList(){
    this->list = new DLinkedList();
    this->size = 0;
}

DOrderedList::~DOrderedList(){
    delete(this->list);
    this->list = NULL;
}
//-------------------------------------------------------------

bool DOrderedList::insert(OrderedData *item){
    bool success = false;
    NodeLL *prev = NULL;
    NodeLL *curr = list->getHead();
    NodeLL *newNode = NULL;
    
    if (item != NULL){
        if (list->getSize() == 0 || item->compareTo((OrderedData *)list->getHead()->getData()) > 0){
            list->addToFront(item);
        } else if (item->compareTo((OrderedData *)list->getTail()->getData()) <= 0){
            list->addToBack(item);
        } else {
            prev = NULL;
            curr = list->getHead();
            
            //loop to insertion position
            while (curr != NULL
                   && ((OrderedData*)curr->getData())->compareTo(item) > 0){
                prev = curr;
                curr = curr->getNext();
            }
            
            newNode = new NodeLL(item, prev, curr);
            if (prev != NULL){
                prev->setNext(newNode);
            }
            if (curr != NULL){
                curr->setPrev(newNode);
            }
        }
        this->size++;
        success = true;
    }
    
    return success;
}

OrderedData* DOrderedList::remove(OrderedData *target){
    Data *ptr_data = NULL;
    OrderedData *ptr_orderedData = NULL;
    
    if (target != NULL){
        ptr_data = list->remove((Data *)target);
        ptr_orderedData = dynamic_cast<OrderedData *>(ptr_data);
    }
        
    return ptr_orderedData;
}

void DOrderedList::destory(OrderedData *target){
    if (target != NULL)
        list->destroy((Data *)target);
}

void DOrderedList::print(){
    this->list->print();
}

//***************** GETTERS ******************
NodeLL* DOrderedList::getHead()
{
    return list->getHead();
}

int DOrderedList::getSize()
{
    return this->size;
}