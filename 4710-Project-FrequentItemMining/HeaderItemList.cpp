#include "HeaderItemList.hpp"
#include "HeaderItem.hpp"
#include "NodeLL.hpp"
#include "FPTreeItem.hpp"

//--------------------------------------------------------------------------//
//  HeaderItemList
//
//  Basically a linked list but contains some methods required specifically
//  for performing functions on header table items.
//--------------------------------------------------------------------------//

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

/**
 * PURPOSE: inserts a given <HeaderItem> into the list sorted by a frequency order
 * RETURNS: returns the same <HeaderItem> item which is passed as a parameter if the 
 *          header table does not already include it, otherwise returns the found 
 *          item in the header table.
 * REMARKS: if the given  <HeaderItem> is found in the table, then it also increase
 *          the support by given <HeaderItem>
 */
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

/**
 * PURPOSE: detaches the node containing the given item from the headerlist
 * RETURNS: returns the <NodeLL> if found in the header list otherwise a NULL 
 *          is returned
 */
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

/**
 * PURPOSE: removes and deletes all the infrequent header items for a given minsup value
 * REMARKS: this method also removes the infrequent items from the linked path nodes
 */
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

//----------------------GETTERS-----------------------------//

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