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

//private - recursive insertion
void FPTreeNode::insertTransaction(FPTreeItem *items[], int size, int curr, HeaderTable *headerTable){
    FPTreeNode *targetNode = NULL;
    
    if (curr < size && curr >= 0 && items[curr] != NULL){
        targetNode = this->incrementChild(items[curr], headerTable);
        if (targetNode != NULL){
            targetNode->insertTransaction(items, size, curr+1, headerTable);
        }
    }
}

// @purpose : increments the count for the given item by 1
FPTreeNode* FPTreeNode::incrementChild(FPTreeItem *target, HeaderTable *headerTable){
    FPTreeNode *targetNode = NULL;
    FPTreeNode *curr = this->headChild;
    FPTreeNode *prev = NULL;
    bool newNodeCreated = false;
    
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

    return targetNode;
}

//compares the FPTreeItems' data between the two
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

void FPTreeNode::print(){
    this->data->print();
}

// @purpose : prints the node's depiction within the tree
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