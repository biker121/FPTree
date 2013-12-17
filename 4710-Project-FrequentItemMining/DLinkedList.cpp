//
//  DLinkedList.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include <iostream>
#include "NodeLL.hpp"
#include "Data.hpp"
#include "DLinkedList.hpp"

using namespace std;

//------------------Constructor/Destructor---------------------
DLinkedList::DLinkedList(){
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

DLinkedList::~DLinkedList(){
    NodeLL *curr = this->head;
    NodeLL *next = NULL;
    
    while (curr != NULL){
        next = curr->getNext();
        delete(curr);
        curr = next;
    }
}//------------------------------------------------------------

bool DLinkedList::addToFront(Data *data){
    bool success = false;
    NodeLL *newNode;
    
    if (data != NULL){
        newNode = new NodeLL(data, NULL, NULL);
        
        if (this->head == NULL && this->tail == NULL){  //empty list
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->setNext(this->head);
            this->head->setPrev(newNode);
            this->head = newNode;
        }
        
        success = true;
        this->size++;
    }
    return success;
}

bool DLinkedList::addToBack(Data *data){
    bool success = false;
    NodeLL *newNode;
    
    if (data != NULL){
        newNode = new NodeLL(data, NULL, NULL);
        
        if (this->head == NULL && this->tail == NULL){  //empty list
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->setPrev(this->tail);
            this->tail->setNext(newNode);
            this->tail = newNode;
        }
        
        success = true;
        this->size++;
    }
    
    return success;
}

// Purpose: Iterates through to find an item which equals to the given target
// Parm   :
// Return : ptr to the node that contains an item equals to the given taget
NodeLL* DLinkedList::find(Data *target){
    NodeLL *curr = this->head;
    
    while (curr != NULL && curr->getData()->isEqualsTo(target) == false){
        curr = curr->getNext();
    }
    
    return curr;
}

// Purpose: removes the given item from the list, if it exists
Data* DLinkedList::remove(Data *target){
    NodeLL *targetNode = find(target);
    Data *item = NULL;
    
    if (targetNode != NULL){
        
        //unlink targetNode
        if (targetNode == this->head && targetNode == this->tail){
            this->head = NULL;
            this->tail = NULL;
        } else if (targetNode == this->head){
            this->head = this->head->getNext();
            if (head != NULL){
                this->head->setPrev(NULL);
            }
        } else if (targetNode == this->tail){
            this->tail = this->tail->getPrev();
            if (this->tail != NULL){
                this->tail->setNext(NULL);
            }
        } else {
            targetNode->getPrev()->setNext(targetNode->getNext());
            targetNode->getNext()->setPrev(targetNode->getPrev());
        }
        
        //remove node
        item = targetNode->getData();
        
        targetNode->setData(NULL);
        delete(targetNode);
        this->size--;
    }
    
    return item;
}

void DLinkedList::destroy(Data *item){
    Data *toDestory = remove(item);
    
    if (toDestory != NULL){
        delete(toDestory);
    }
}

// PURPOSE: prints each data item on a line
void DLinkedList::print(){
    NodeLL *curr = this->head;
    
    while (curr != NULL){
        curr->getData()->print();        
        curr = curr->getNext();
    }
    cout << endl;
}

//************ GETTERS *************
NodeLL* DLinkedList::getHead(){
    return this->head;
}
NodeLL* DLinkedList::getTail(){
    return this->tail;
}
int DLinkedList::getSize(){
    return size;
}

//************ SETTERS *************
void DLinkedList::setHead(NodeLL *head){
    this->head = head;
}
void DLinkedList::setTail(NodeLL *tail){
    this->head = tail;
}
void DLinkedList::setSize(int size){
    this->size = size;
}