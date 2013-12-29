#ifndef _710_Project_FrequentItemMining_FPTreeItem_hpp
#define _710_Project_FrequentItemMining_FPTreeItem_hpp

#include "OrderedData.hpp"

using namespace std;

class HeaderTable;
class FPTreeItem;

class FPTreeItem : public OrderedData
{
    
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
    
    //----------------MINOR METHODS---------------------------//
    int compareTo(OrderedData *item);        // compares frequency
    bool isEqualsTo(OrderedData *target);    // compares data value
    
    void print();
    
    //----------------GETTERS---------------------------------//
    int getData();
    int getSupport();
};

#endif