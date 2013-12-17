//
//  HeaderItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTreeItem.hpp"
#include "HeaderItem.hpp"
#include "FPTreeNode.hpp"
#include "NodeLL.hpp"
#include "PathItem.hpp"

//------------------------Constructors and destructors-----------------------
HeaderItem::HeaderItem(FPTreeItem *data){
    this->data = data;
    this->firstSimilarTreeNode = NULL;
    this->firstPathNode = NULL;
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

/*-------------------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * REMARKS:
 *-----------------------------------------------------------------------------------*/
void HeaderItem::linkPathNode(NodeLL *pathNode, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    int hashIndex = 0;
    PathItem *temp;
    
    if (pathNode != NULL && pathNode->getData() != NULL){
        temp = dynamic_cast<PathItem *>(pathNode->getData());
        
        if (temp != NULL && temp->getData() != NULL){
            hashIndex = HeaderTable::getHashIndex(temp->getData());
            
            if (hashIndex != -1 && hash[hashIndex] != NULL){ //if frequent
                temp->setNextSimilarPathNode(hash[hashIndex]->getFirstPathNode());
                hash[hashIndex]->setFirstPathNode(pathNode);
            }
        }
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: compares the frequency of two HeaderItems
 * PARM   : HeaderItem - item that is being compared
 * RETURN : <0 = 'this' item is less frequent
 *           0 = same frequency
 *          >0 = 'this' item is more frequent
 * REMARKS: NULL items are taken as lowest priority
 *-----------------------------------------------------------------------------------*/
int HeaderItem::compareTo(OrderedData *other){
    HeaderItem *otherItem = NULL;
    int result = 1;
    
    if (other != NULL && (otherItem = dynamic_cast<HeaderItem *>(other)) != NULL)
        result = this->data->compareTo(otherItem->data);
//        result = this->getNode()->getData()->compareTo(otherItem->getNode()->getData());
    
    return result;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: prints priority, data value, frequency (e.g. "{10} 22 : 1")
 *-----------------------------------------------------------------------------------*/
void HeaderItem::print(){
    this->data->print();
    cout << endl;
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

//***************** SETTERS ******************
void HeaderItem::setFirstSimilarTreeNode(FPTreeNode *firstSimilarTreeNode)
{
    this->firstSimilarTreeNode = firstSimilarTreeNode;
}

void HeaderItem::setFirstPathNode(NodeLL *firstPathNode)
{
    this->firstPathNode = firstPathNode;
}
