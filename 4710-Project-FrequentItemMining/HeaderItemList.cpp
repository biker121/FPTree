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
#include "FPTreeItem.hpp"

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
    NodeLL *extractedNode = NULL;
    
    if(head == NULL && tail == NULL)
    {
        head = newNode;
        tail = head;
        targetItem = item;
    }else {
        
        if( item != NULL && item->getData() != NULL) {
            extractedNode = extract(item->getData()->getData());
            if(extractedNode==NULL) {
                targetItem = item;
                orderedInsert(item);
            }else {
                targetItem = (HeaderItem*)extractedNode->getData();
                targetItem->increaseSupport(item->getData()->getSupport());
                orderedInsert(targetItem);
            }
        }
    }
    
    return targetItem;
}

NodeLL* HeaderItemList::extract(int item)
{
    NodeLL *curr = head;
    NodeLL *currPrev = NULL;
    NodeLL *currNext = NULL;
    NodeLL *result = NULL;
    
    HeaderItem *currItem = NULL;
    bool found = false;
    while (!found && curr !=NULL)
    {
        currItem = dynamic_cast<HeaderItem*>(curr->getData());
        
        if(currItem!=NULL && currItem->getData() != NULL) {
            found = currItem->getData()->getData() == item;
            
            if(found) {
                result = curr;
                
                currNext = curr->getNext();
                currPrev = curr->getPrev();
                
                if(curr == head) {
                    head = currNext;
                    
                    if(currNext!=NULL)
                        currNext->setPrev(NULL);
                }else if(curr == tail) {
                    tail = currPrev;
                    
                    if(currPrev!=NULL)
                        currPrev->setNext(NULL);
                }else {
                    currPrev->setNext(currNext);
                    currNext->setPrev(currPrev);
                }
                
                curr->setNext(NULL);
                curr->setPrev(NULL);
            }
        }
        
        curr = curr->getNext();
    }
    
    return result;
}

void HeaderItemList::orderedInsert(HeaderItem *item)
{
    orderedInsert(new NodeLL(item));
}

// Only used for global tree header tables
void HeaderItemList::orderedInsert(NodeLL *newNode)
{    
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

HeaderItem* HeaderItemList::getItem(FPTreeItem *item)
{
    bool found = false;
    HeaderItem *itemFound = NULL;
    HeaderItem *temp = NULL;
    FPTreeItem *tempFPItem = NULL;
    
    NodeLL *curr = head;
    while (!found && curr!=NULL) {
        temp = (HeaderItem*)curr->getData();
        
        if(temp != NULL)
        {
            tempFPItem = (FPTreeItem*)temp->getData();
            
            //DEBUG print
//            cout << "Comparting:";
//            tempFPItem->print();
//            cout << " with ";
//            item->print();
//            cout << "\n";
            
            if (tempFPItem != NULL && tempFPItem->getData()==item->getData())
            {
                itemFound = temp;
                found = true;
            }
        }
        
        curr = curr->getNext();
    }
    return itemFound;
}

void HeaderItemList::removeInfrequent(int minsup)
{
    NodeLL *curr = head;
    HeaderItem *currHItem = NULL;
    FPTreeItem *currItem = NULL;
    NodeLL *tempNext = NULL;
    int infreqId = 0;
    
    while (curr!=NULL)
    {
        currHItem = (HeaderItem*)curr->getData();
        currItem = currHItem->getData();
        
        // get next pointer as this node might get destroyed if infreq
        tempNext = curr->getNext();
        
        if(currItem !=NULL && currItem->getSupport() < minsup)
            infreqId++;
        
        if(infreqId==1)
            curr->setNext(NULL);
        else if(infreqId>1) {
            currHItem->removeInfreqPathItems();
            delete (curr);
        }
        
        curr = tempNext;
    }
}
