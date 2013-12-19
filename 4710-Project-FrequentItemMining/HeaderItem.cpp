//
//  HeaderItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//
//
//  HeaderItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTreeItem.hpp"
#include "HeaderItem.hpp"
#include "HeaderTable.hpp"
#include "FPTreeNode.hpp"
#include "NodeLL.hpp"
#include "TransPathItem.hpp"

//------------------------Constructors and destructors-----------------------
HeaderItem::HeaderItem(FPTreeItem *data){
    this->data = data;
    this->firstSimilarTreeNode = NULL;
    this->firstPathNode = NULL;
    this->similarNodeCount = 0;
}
HeaderItem::~HeaderItem(){ //requires others to destroy path and tree nodes
    delete(data);
    
    this->data = NULL;
    this->firstPathNode = NULL;
    this->firstSimilarTreeNode = NULL;
}//--------------------------------------------------------------------------

/*-------------------------------------------------------------------------------------
 * PURPOSE: adds the link to the given node for the appropriate headerItem
 * PARM   : *node - that is to be linked to the header table
 * REMARKS: - this method links the node without question
 *-----------------------------------------------------------------------------------*/
void HeaderItem::linkTreeNode(FPTreeNode *treeNode, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    int hashIndex = 0;
    
    if (treeNode != NULL){
        hashIndex = HeaderTable::getHashIndex(treeNode->getData());
        
        if (hashIndex != -1 && hash[hashIndex] != NULL){ //if frequent
            treeNode->setNextSimilarNode(hash[hashIndex]->getFirstSimilarTreeNode());
            hash[hashIndex]->setFirstSimilarTreeNode(treeNode);
        }
    }
}

void HeaderItem::linkNextPath(NodeLL *pathNodeToLink)
{
    if(this->firstPathNode==NULL) {
        firstPathNode = pathNodeToLink;
        lastPathNode = pathNodeToLink;
    }else {
        TransPathItem *pathItem = dynamic_cast<TransPathItem*>(lastPathNode->getData());
        pathItem->setNextPathNode(pathNodeToLink);
        lastPathNode = pathNodeToLink;
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: compares the frequency of two domain items 
 * PARM   : HeaderItem - item that is being compared
 * RETURN : <0 = 'this' item is less frequent
 *           0 = same item regardless of frequency
 *          >0 = 'this' item is more frequent
 * REMARKS: NULL items are taken as lowest priority
 *-----------------------------------------------------------------------------------*/
int HeaderItem::compareTo(OrderedData *other){
    HeaderItem *otherItem = dynamic_cast<HeaderItem *>(other);
    FPTreeItem *otherData = otherItem->getData();
    int result = 1;
    
    if (otherItem != NULL)
    {
        if (this->data->getData() == otherData->getData())
        {
            result = 0;
        } else if(this->data->getSupport() < otherData->getSupport())
        {
            result = -1;
        } else if(this->data->getSupport() == otherData->getSupport())
        {
            if (this->data->getData() > otherData->getData())
            {
                result = 1;
            } else
            {
                result = -1;
            }
        }
    }
    return result;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: prints priority, data value, frequency (e.g. "{10} 22 : 1")
 *-----------------------------------------------------------------------------------*/
void HeaderItem::print(){
    this->data->print();
    cout << endl;
}

void HeaderItem::increaseSupport()
{
    if(data!=NULL)
    {
        data->increaseSupport();
    }
}

//***************** GETTERS ******************
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
    return similarNodeCount;
}

NodeLL* HeaderItem::getLastPathNode()
{
    return lastPathNode;
}

//***************** SETTERS ******************
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