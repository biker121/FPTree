//
//  TransPathItem.h
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-16.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef ___710_Project_FrequentItemMining__TransPathItem__
#define ___710_Project_FrequentItemMining__TransPathItem__

#include "OrderedData.hpp"

class FPTreeItem;
class NodeLL;

class TransPathItem : public OrderedData {
    
private:
    FPTreeItem *item;
    NodeLL *nextPathNode;
    
public:
    TransPathItem(FPTreeItem *data, NodeLL *nextNode);
    virtual ~TransPathItem();
    
    int compareTo(OrderedData *other);
    void print();
    
    //**************** GETTERS *******************
    FPTreeItem* getItem();
    NodeLL* getNextPathNode();
    
    //**************** SETTERS *******************
    void setNextPathNode(NodeLL* next);
    void setItem(FPTreeItem* item);
};

#endif