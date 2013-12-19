//
//  HeaderItemList.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-17.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderItemList.hpp"

#include "HeaderItem.hpp"
#include "NodeLL.hpp"

HeaderItemList::HeaderItemList()
{
    head = NULL;
    tail = NULL;
}

HeaderItemList::~HeaderItemList()
{
    NodeLL* curr = head;
    while (curr!=NULL) {
        delete (curr);
        curr = curr->getNext();
    }
}

// used for projected tree header tables
HeaderItem* HeaderItemList::insertByFreqOrder(HeaderItem *item)
{
    HeaderItem *targetItem = NULL;
    NodeLL *newNode = new NodeLL(item);
    
    if(head == NULL && tail == NULL)
    {
        head = newNode;
        tail = head;
        targetItem = item;
    }else {
        
        NodeLL* curr = tail;
        bool done = false;
        while (!done && curr!=NULL)
        {
            if(newNode->getData()->compareTo(curr->getData()) == -1)
            {
                NodeLL *temp = curr->getNext();
                
                curr->setNext(newNode);
                newNode->setPrev(curr);
                
                if(temp!=NULL) {
                    newNode->setNext(temp);
                    temp->setPrev(newNode);
                }else {
                    // set new tail
                    tail = newNode;
                }
                
                targetItem = item;
                done = true;
                
            }else if(newNode->getData()->compareTo(curr->getData()) == 0)
            {
                // we dont need this node because we merge it
                delete (newNode);
                
                // increament the support by 1
                dynamic_cast<HeaderItem*>(curr->getData())->increaseSupport();
                targetItem = dynamic_cast<HeaderItem*>(curr->getData());
                
                // switch with previous node, if frequency is now greater
                NodeLL* prev = curr->getPrev();
                if(prev != NULL)
                {
                    // if merger node is bigger than its previous node
                    if(curr->getData()->compareTo(prev->getData()) == 1)
                    {
                        NodeLL *temp = curr->getNext();
                        NodeLL *nextNext = temp->getNext();
                        NodeLL *prevPrev = prev->getPrev();
                        
                        if (prevPrev!=NULL)
                            prevPrev->setNext(curr);
                        else
                            head = curr; // set new head
                        
                        curr->setNext(prev);
                        curr->setPrev(prev->getPrev());
                        
                        if(nextNext!=NULL)
                            nextNext->setPrev(prev);
                        
                        prev->setNext(temp);
                        prev->setPrev(curr);
                    }
                }
                
                done = true;
            }else
            {
                curr = curr->getPrev();
            }
        }
    }
        
    return targetItem;
}

// Only used for global tree header tables
void HeaderItemList::orderedInsert(HeaderItem *item)
{
    NodeLL *newNode = new NodeLL(item);
    
    if(head == NULL)
    {
        head = newNode;
        tail = newNode;
    }else
    {
        bool done = false;
        NodeLL* curr = head;
        while (!done)
        {
            if(newNode->getData()->compareTo(curr->getData()) == 1)
            {
                NodeLL *temp = curr->getPrev();
                
                newNode->setNext(curr);
                curr->setPrev(newNode);
                
                if(temp!=NULL) {
                    temp->setNext(newNode);
                    newNode->setPrev(temp);
                }else {
                    // set new head
                    head = newNode;
                }
                
                done = true;
            }
            
            // last node
            if(curr->getNext()== NULL && !done)
            {
                curr->setNext(newNode);
                newNode->setPrev(curr);
                
                tail = newNode;
                done = true;
            }
            
            curr = curr->getNext();
        }
    }
}

void HeaderItemList::print()
{
    NodeLL* curr = head;
    while (curr!=NULL) {
        curr->getData()->print();
        curr = curr->getNext();
    }
    
}

//****************** GETTERS *******************
NodeLL* HeaderItemList::getHeadNode()
{
    return head;
}

NodeLL* HeaderItemList::getTailNode()
{
    return tail;
}