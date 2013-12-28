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
    while (curr!=NULL)
    {
        delete (curr);
        curr = curr->getNext();
    }
}

// used for projected tree header tables
HeaderItem* HeaderItemList::insertByFreqOrder(HeaderItem *item)
{
    HeaderItem *targetItem = NULL;
    NodeLL *extractedNode = NULL;
    
    NodeLL *newNode = new NodeLL(item);
    
    if(head == NULL && tail == NULL)
    {
        head = newNode;
        tail = head;
        targetItem = item;
    }else
    {
        
        if( item != NULL && item->getData() != NULL)
        {
            extractedNode = extract(item->getData()->getData());
            if(extractedNode==NULL)
            {
                targetItem = item;
                orderedInsert(item);
            }else
            {
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
        
        if(currItem!=NULL && currItem->getData() != NULL)
        {
            found = currItem->getData()->getData() == item;
            
            if(found)
            {
                result = curr;
                
                currNext = curr->getNext();
                currPrev = curr->getPrev();
                
                if(curr == head)
                {
                    head = currNext;
                    
                    if(currNext!=NULL)
                        currNext->setPrev(NULL);
                }else if(curr == tail)
                {
                    tail = currPrev;
                    
                    if(currPrev!=NULL)
                        currPrev->setNext(NULL);
                }else
                {
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

void HeaderItemList::orderedInsert(NodeLL *newNode)
{
    
    NodeLL* curr = NULL;
    NodeLL *temp = NULL;
    bool done = false;
    
    if(head == NULL)
    {
        head = newNode;
        tail = newNode;
    }else
    {
        curr = head;
        while (!done)
        {
            if(newNode->getData()->compareTo(curr->getData()) == 1)
            {
                temp = curr->getPrev();
                
                newNode->setNext(curr);
                curr->setPrev(newNode);
                
                if(temp!=NULL)
                {
                    temp->setNext(newNode);
                    newNode->setPrev(temp);
                }else
                    head = newNode; // set new head
                
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

void HeaderItemList::removeInfrequent(int minsup)
{
    HeaderItem *currHItem = NULL;
    FPTreeItem *currItem = NULL;
    NodeLL *tempNext = NULL;
    
    int infreqId = 0;
    
    NodeLL *curr = head;
    
    while (curr!=NULL)
    {
        currHItem = (HeaderItem*)curr->getData();
        currItem = (FPTreeItem*)currHItem->getData();
        
        // get next pointer as this node might get destroyed if infreq
        tempNext = curr->getNext();
        
        if(currItem !=NULL && currItem->getSupport() < minsup)
            infreqId++;
        
        if(infreqId>=1) {
            if(infreqId==1)
            {
                if(curr->getPrev()!=NULL) {
                    curr->getPrev()->setNext(NULL);
                    tail = curr->getPrev();
                }else {
                    head = NULL;
                    tail = NULL;
                }
            }
            
            currHItem->removeInfreqPathItems();
            
            delete (curr);
        }
        
        curr = tempNext;
    }
}

void HeaderItemList::print()
{
    NodeLL* curr = head;
    while (curr!=NULL)
    {
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
    FPTreeItem *tempFPItem = NULL;
    HeaderItem *temp = NULL;
    
    NodeLL *curr = head;
    while (!found && curr!=NULL)
    {
        temp = (HeaderItem*)curr->getData();
        
        if(temp != NULL)
        {
            tempFPItem = (FPTreeItem*)temp->getData();
            
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

int HeaderItemList::getSize()
{
    NodeLL *curr = head;
    int size=0;
    
    while (curr!=NULL) {
        size++;
        curr=curr->getNext();
    }
    
    return size;
}