//
//  FPTreeNode.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/27/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderTable.hpp"
#include "FPTreeNode.hpp"

//------------------------Constructors and destructors-----------------------
FPTreeNode::FPTreeNode(){
    this->data = 0;
    this->nextSimilarNode = NULL;
    this->parent = NULL;
    this->nextSibling = NULL;
    this->headChild = NULL;
}
FPTreeNode::FPTreeNode(FPTreeItem *data, FPTreeNode *parent, FPTreeNode *nextSibling){
    this->data = data;
    this->parent = parent;
    this->nextSibling = nextSibling;
    
    this->nextSimilarNode = NULL;
    this->headChild = NULL;
}
FPTreeNode::~FPTreeNode(){
    delete(data);
    
    if (nextSibling != NULL)
        delete(nextSibling);
    if (headChild != NULL)
        delete(headChild);
}//--------------------------------------------------------------------------

/*-------------------------------------------------------------------------------------
 * PURPOSE: adds target as one of its children
 * PARM   : *target - item that is to be added as a child
 * PARM   : *headerTable - for used for linking new nodes to the table
 * RETURN : returns a ptr to the child that is added
 * REMARKS: if 'this' already contains a child similar to target, it increments the
 *          child's frequency instead of adding a new node
 *-----------------------------------------------------------------------------------*/
FPTreeNode* FPTreeNode::incrementChild(FPTreeItem *target, HeaderTable *headerTable){
    FPTreeNode *targetNode = NULL;
    FPTreeNode *curr = this->headChild;
    FPTreeNode *prev = NULL;
    bool newNodeCreated = false;
    
    if (target != NULL && headerTable != NULL){
        //cycle to correct location
        while (curr != NULL && curr->getData() != NULL &&
               curr->compareTo(target) <= 0){
            prev = curr;
            curr = curr->getNextSibling();
        }
        
        if (prev == NULL){
            targetNode = new FPTreeNode(target, this, this->headChild);
            newNodeCreated = true;
            this->headChild = targetNode;
        } else {
            if (prev->compareTo(target) == 0){   //node already exists
                prev->data->increment();
                targetNode = prev;
            } else {
                targetNode = new FPTreeNode(target, this, curr);
                newNodeCreated = true;
                prev->nextSibling = targetNode;
            }
        }
        
        //add node link to header table if a new node was created
        if (newNodeCreated){
            headerTable->linkNode(targetNode);
        }
    }
    return targetNode;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: sequentially inserts the given items into 'this' node structure
 * PARM   : pre-sorted items that are to be inserted
 * PARM   : size - length of the items[] array
 * PARM   : curr - pos of the current item that is being processed
 * PARM   : headerTable - used only for linking new nodes to the headerTable
 * REMARKS: - items[] must be prioritized and contain only frequent items
 *-----------------------------------------------------------------------------------*/
void FPTreeNode::insertTransaction(FPTreeItem *items[], int size, int curr, HeaderTable *headerTable){
    FPTreeNode *targetNode = NULL;
    
    if (headerTable != NULL && items != NULL){
        if (curr < size && curr >= 0 && items[curr] != NULL){
            targetNode = this->incrementChild(items[curr], headerTable);
            if (targetNode != NULL){
                targetNode->insertTransaction(items, size, curr+1, headerTable);
            }
        }
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: compares based on alphabetical order and returns an integer representing
 *          result of comparison
 * PARM   : *OrderedItem , item that is to be compared
 * PARM   : 0  -> if both have similar data value
 *        : +1 -> current tree would appear after  the given, in a sorted order
 *        : -1 -> current tree swould appear before the given, in a sorted order
 *-----------------------------------------------------------------------------------*/
int FPTreeNode::compareTo(OrderedData *item){
    FPTreeNode *otherFPTreeNode = dynamic_cast<FPTreeNode *>(item);
    FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(item);
    
    int result = 0;
    
    if (otherFPTreeNode != NULL)
        result = this->data->getData() - otherFPTreeNode->data->getData();
    else if (otherFPTreeItem != NULL)
        result = this->data->getData() - otherFPTreeItem->getData();
    return result;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: prints the contents of the current node
 *-----------------------------------------------------------------------------------*/
void FPTreeNode::print(){
    this->data->print();
}

// @purpose : prints the node's depiction within the tree
/*-------------------------------------------------------------------------------------
 * PURPOSE: prints the current node and invokes print() on a sibling and first children
 * PARM   : level - to identify pad space
 *-----------------------------------------------------------------------------------*/
void FPTreeNode::print(int level){
    stringstream ss;
    
    //pad '-'
    for (int i=0; i<level; i++){
        ss << "-";
    }
    
    //process self
    if (this->data == NULL){
        ss << "root";
    } else {
        ss << this->data->getData() << " : " << this->getData()->getFrequency() ;
    }
    cout << ss.str() << endl;;
    
    //process children
    if (this->getHeadChild() != NULL){
        this->getHeadChild()->print(level+1);
    }
    
    //process sibling
    if (this->getNextSibling() != NULL){
        this->getNextSibling()->print(level);
    }
}

//********************** GETTERS ***********************
FPTreeItem* FPTreeNode::getData(){ return this->data; }
FPTreeNode* FPTreeNode::getNextSimilarNode(){ return this->nextSimilarNode; }
FPTreeNode* FPTreeNode::getParent(){ return this->parent; }
FPTreeNode* FPTreeNode::getNextSibling(){ return this->nextSibling; }
FPTreeNode* FPTreeNode::getHeadChild(){ return this->headChild; }

//********************** Setters ***********************
void FPTreeNode::setNextSibling(FPTreeNode *nextSibling){
    this->nextSibling = nextSibling;
}

void FPTreeNode::setNextSimilarNode(FPTreeNode *nextSimilarNode){
    this->nextSimilarNode = nextSimilarNode;
}