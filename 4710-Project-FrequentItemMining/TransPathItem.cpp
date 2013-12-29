#include <iostream>

#include "TransPathItem.hpp"
#include "OrderedData.hpp"
#include "FPTreeItem.hpp"
#include "NodeLL.hpp"
#include "DLinkedList.hpp"

//--------------------------------------------------------------------------//
//  TransPathItem
//
//  Data type for a transaction path list, which is used while building paths
//  for projected trees. This object contains a <FPTree> data item and a link to
//  the next similar path node, which is later set when reading paths.
//  A link to the parent <DLinkedList> of the next similar node is also stored
//  as it is required for properly removing the item from the list.
//--------------------------------------------------------------------------//

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

//----------------------MINOR METHODS-----------------------//

int TransPathItem::compareTo(OrderedData *other)
{
    return -1;
}

void TransPathItem::print()
{
    if (item != NULL)
        this->item->print();
}

//----------------------GETTERS-----------------------------//

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

//----------------------SETTERS-----------------------------//

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