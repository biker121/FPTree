//
//  PathItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "PathItem.hpp"
#include "NodeLL.hpp"
#include "FPTreeItem.hpp"

PathItem::PathItem(FPTreeItem *data){
    this->data = data;
    this->nextSimilarPathNode = NULL;
}
PathItem::~PathItem(){
    delete(data);
    this->data = NULL;
    this->nextSimilarPathNode = NULL;
}

//************** GETTERS ****************
FPTreeItem* PathItem::getData(){
    return this->data;
}
NodeLL* PathItem::getNextSimilarPathNode(){
    return this->nextSimilarPathNode;
}

//************** SETTERS ****************
void PathItem::setData(FPTreeItem *data){
    this->data = data;
}

void PathItem::setNextSimilarPathNode(NodeLL *nextSimilarPathNode){
    this->nextSimilarPathNode = nextSimilarPathNode;
}