#include "FPTreeItem.hpp"
#include "HeaderItem.hpp"
#include "HeaderTable.hpp"
#include "FPTreeNode.hpp"
#include "NodeLL.hpp"
#include "TransPathItem.hpp"
#include "DLinkedList.hpp"

//--------------------------------------------------------------------------//
//  HeaderItem
//
//  <HeaderTable> data type containing <FPTreeItem>, a link to the next
//  similar node in the <FPTree>, and also a link to the first node in
//  transaction path list
//--------------------------------------------------------------------------//

HeaderItem::HeaderItem(FPTreeItem *data)
{
    this->data = data;
    this->firstSimilarTreeNode = NULL;
    this->firstPathNode = NULL;
}

/**
 * PURPOSE: requires others to destroy path and tree nodes
 */
HeaderItem::~HeaderItem()
{
    delete(data);
    this->data = NULL;
    this->firstPathNode = NULL;
    this->firstSimilarTreeNode = NULL;
}

/**
 * PURPOSE: removes and deletes all the path nodes by chasing the links
 *          from the first path node
 * REMARKS: this method is called when a header item is found to be infrequent
 *          and as a result this removes the similar infrequent items from all 
 *          the transaction paths
 */
void HeaderItem::removeInfreqPathItems()
{
    NodeLL *pathNode = firstPathNode;
    NodeLL *nextPath = NULL;
    TransPathItem *pathItem = NULL;
    DLinkedList *currPathList = NULL;
    
    while (pathNode!=NULL)
    {
        pathItem = (TransPathItem*)pathNode->getData();
        currPathList = pathItem->getPathList();

        // get pointer to next path before destroying node
        nextPath = pathItem->getNextPathNode();
        
        if(currPathList != NULL)
            currPathList->remove(pathNode);
                
        // dont delete because it is done by the currPathList itself
        
        pathNode = nextPath;
    }
}

/**
 * PURPOSE: adds the link to the given node for the appropriate headerItem
 * PARAM  : treenode to be linked to the header table
 * REMARKS: this method links the node without question
 */
void HeaderItem::linkTreeNode(FPTreeNode *treeNode, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    FPTreeNode *curr = firstSimilarTreeNode;
    bool done = false;
    
    if(curr==NULL)
    {
        setFirstSimilarTreeNode(treeNode);
    }else
    {
        while (curr != NULL && !done)
        {
            if(curr->getNextSimilarNode()==NULL)
            {
                curr->setNextSimilarNode(treeNode);
                done = true;
            }
            
            if(!done)
                curr = curr->getNextSimilarNode();
        }
    }
}

/**
 * PURPOSE: links the last similar node the give <NodeLL> and sets it as the last
 *          path similar node
 * PARAM  : Node pointer to be linked
 */
void HeaderItem::linkNextPath(NodeLL *pathNodeToLink)
{
    TransPathItem *pathItem = NULL;
    
    if(this->firstPathNode==NULL)
    {
        this->firstPathNode = pathNodeToLink;
        this->lastPathNode = pathNodeToLink;
    }else
    {
        pathItem = dynamic_cast<TransPathItem*>(lastPathNode->getData());
        if(pathItem!=NULL)
        {
            pathItem->setNextPathNode(pathNodeToLink);
            this->lastPathNode = pathNodeToLink;
        }
    }
}

/**
 * PURPOSE: compares the frequency of two domain items 
 * PARM   : HeaderItem being compared
 * RETURN : <0 = 'this' item is less frequent
 *           0 = same item regardless of frequency
 *          >0 = 'this' item is more frequent
 * REMARKS: NULL items are taken as lowest priority
 */
int HeaderItem::compareTo(OrderedData *other)
{
    HeaderItem *otherItem = dynamic_cast<HeaderItem *>(other);
    FPTreeItem *otherData = otherItem->getData();
    int result = 1;
    
    if (otherItem != NULL)
    {
        if (this->data->getData() == otherData->getData())
            result = 0;
        else if(this->data->getSupport() < otherData->getSupport())
            result = -1;
        else if(this->data->getSupport() == otherData->getSupport())
        {
            if (this->data->getData() < otherData->getData())
                result = 1;
            else
                result = -1;
        }
    }
    return result;
}

/**
 * PURPOSE: prints priority, data value, frequency (e.g. "{10} 22 : 1")
 */
void HeaderItem::print()
{
    this->data->print();
    cout << endl;
}

void HeaderItem::increaseSupport()
{
    if(data!=NULL)
        data->increaseSupport();
}

void HeaderItem::increaseSupport(int inc)
{
    if(data!=NULL)
        data->increaseSupport(inc);
}

//--------------------GETTERS------------------------//

FPTreeItem* HeaderItem::getData()
{
    return this->data;
}

FPTreeNode* HeaderItem::getFirstSimilarTreeNode()
{
    return this->firstSimilarTreeNode;
}

NodeLL* HeaderItem::getFirstPathNode()
{
    return this->firstPathNode;
}

int HeaderItem::getSimilarNodeCount()
{
    int similarNodeCount = 0;
    
    FPTreeNode *curr = this->firstSimilarTreeNode;
    while (curr!=NULL)
    {
        similarNodeCount++;
        curr = curr->getNextSimilarNode();
    }
    
    return similarNodeCount;
}

NodeLL* HeaderItem::getLastPathNode()
{
    return lastPathNode;
}

//--------------------SETTERS------------------------//

void HeaderItem::setFirstSimilarTreeNode(FPTreeNode *firstSimilarTreeNode)
{
    this->firstSimilarTreeNode = firstSimilarTreeNode;
}

void HeaderItem::setFirstPathNode(NodeLL *firstPathNode)
{
    this->firstPathNode = firstPathNode;
}

void HeaderItem::setLastPathNode(NodeLL *lastPathNode)
{
    this->lastPathNode = lastPathNode;
}