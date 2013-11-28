//
//  FPTreeNode.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/27/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

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
void FPTreeNode::insertTransaction(FPTreeItem *items[], int size, int curr){
    FPTreeNode *targetNode = NULL;
    
    if (curr < size && curr >= 0 && items[curr] != NULL){
        targetNode = this->incrementChild(items[curr]);
        if (targetNode != NULL){
            targetNode->insertTransaction(items, size, curr+1);
        }
    }
}

// @purpose : increments the count for the given item by 1
FPTreeNode* FPTreeNode::incrementChild(FPTreeItem *target){
    FPTreeNode *targetNode = NULL;
    FPTreeNode *curr = this->headChild;
    FPTreeNode *prev = NULL;
    
    //cycle to correct location
    while (curr != NULL && curr->getData() != NULL &&
           curr->getData()->compareTo(target) <= 0){
        prev = curr;
        curr = curr->getNextSibling();
    }
    
    if (prev == NULL){
        targetNode = new FPTreeNode(target, this, this->headChild);
        this->headChild = targetNode;
    } else {
        
        if (prev->getData()->compareTo(target) == 0){   //node already exists
            prev->data->increment();
            targetNode = prev;
        } else {
            targetNode = new FPTreeNode(target, this, curr);
            prev->nextSibling = targetNode;
        }
    }
    
    return targetNode;
}

//compares the FPTreeItems' data between the two
int FPTreeNode::compareTo(OrderedData *item){
    FPTreeNode *otherFPTreeNode = dynamic_cast<FPTreeNode *>(item);
    int result = 0;
    
    if (otherFPTreeNode != NULL)
        result = this->data->getData() - otherFPTreeNode->data->getData();
    
    return result;
}

void FPTreeNode::print(){}

void FPTreeNode::print(int level){
    stringstream ss;
    
    //pad '-'
    for (int i=0; i<level; i++)
        ss << "-";
    
    //process self
    ss << this->data << " : " << this->getData()->getFrequency() ;
    cout << ss.str();
    
    //process children
    this->getHeadChild()->print(level+1);
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