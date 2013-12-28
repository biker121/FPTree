#ifndef _710_Project_FrequentItemMining_FPTreeItem_hpp
#define _710_Project_FrequentItemMining_FPTreeItem_hpp

#include "OrderedData.hpp"

using namespace std;

class HeaderTable;
class FPTreeItem;

//-----------------------------------------------------------------------
// CLASS: FPTreeItem
//
// Author: Brahmdeep Singh Juneja
//
// REMARKS: Designed to be used as both header item and node data item
//-----------------------------------------------------------------------
class FPTreeItem : public OrderedData {
    
private:
    int data;
    int support;
    
public:
    FPTreeItem();
    FPTreeItem(int data, int support);
    virtual ~FPTreeItem();
    
    void increaseSupport();
    void increaseSupport(int inc);
    void increaseSupport(FPTreeItem *item);
    
    //*****************Minor Methods********************
    int compareTo(OrderedData *item);       //compares frequency
    void print();
    bool isEqualsTo(OrderedData *target);    //compares data value
    
    //************ Getters ********
    int getData();
    int getSupport();
};

#endif