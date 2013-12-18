//
//  TransPathItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-16.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//
#include <iostream>

#include "TransPathItem.h"
#include "OrderedData.hpp"
#include "FPTreeItem.hpp"
#include "NodeLL.hpp"

TransPathItem::TransPathItem(FPTreeItem *item, NodeLL *nextNode)
{
    this->item = item;
    this->nextPathNode = nextNode;
}

TransPathItem::~TransPathItem()
{
    delete(item);
}

void TransPathItem::setNextPathNode(NodeLL *next)
{
    this->nextPathNode = next;
}

void TransPathItem::setItem(FPTreeItem *item)
{
    this->item = item;
}

FPTreeItem* TransPathItem::getItem()
{
    return this->item;
}

NodeLL* TransPathItem::getNextPathNode()
{
    return this->nextPathNode;
}

int TransPathItem::compareTo(OrderedData *other)
{
    return -1;
}

void TransPathItem::print()
{
    
}
