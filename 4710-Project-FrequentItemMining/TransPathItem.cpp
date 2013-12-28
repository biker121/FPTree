#include <iostream>

#include "TransPathItem.hpp"
#include "OrderedData.hpp"
#include "FPTreeItem.hpp"
#include "NodeLL.hpp"
#include "DLinkedList.hpp"

TransPathItem::TransPathItem(FPTreeItem *item, DLinkedList *pathList)
{
    this->item = item;
    this->nextPathNode = NULL;
    this->pathList = pathList;
}

TransPathItem::~TransPathItem()
{
    delete(item);
    this->nextPathNode = NULL;
    this->pathList = NULL;
}

//******************* MINOR METHODS *****************

int TransPathItem::compareTo(OrderedData *other)
{
    return -1;
}

void TransPathItem::print()
{
    if (item != NULL)
        this->item->print();
}

//**************** GETTERS *******************

FPTreeItem* TransPathItem::getItem()
{
    return this->item;
}

NodeLL* TransPathItem::getNextPathNode()
{
    return this->nextPathNode;
}

DLinkedList* TransPathItem::getPathList()
{
    return pathList;
}

//**************** SETTERS *******************

void TransPathItem::setNextPathNode(NodeLL *next)
{
    this->nextPathNode = next;
}

void TransPathItem::setItem(FPTreeItem *item)
{
    this->item = item;
}

void TransPathItem::setPathList(DLinkedList *pathList)
{
    this->pathList = pathList;
}