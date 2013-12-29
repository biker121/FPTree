#ifndef ___710_Project_FrequentItemMining__TransPathItem__
#define ___710_Project_FrequentItemMining__TransPathItem__

#include "OrderedData.hpp"

class FPTreeItem;
class NodeLL;
class DLinkedList;

class TransPathItem : public OrderedData
{
    
private:
    FPTreeItem *item;
    NodeLL *nextPathNode;
    DLinkedList *pathList;
    
public:
    TransPathItem(FPTreeItem *data, DLinkedList *pathList);
    virtual ~TransPathItem();
    
    int compareTo(OrderedData *other);
    void print();
    
    //----------------------GETTERS-------------------------//
    FPTreeItem* getItem();
    NodeLL* getNextPathNode();
    DLinkedList* getPathList();
    
    //----------------------SETTERS-------------------------//
    void setPathList(DLinkedList *pathList);
    void setNextPathNode(NodeLL* next);
    void setItem(FPTreeItem* item);
};

#endif