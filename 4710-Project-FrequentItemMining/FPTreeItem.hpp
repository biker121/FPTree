//
//  FPTreeItem.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTreeItem_hpp
#define _710_Project_FrequentItemMining_FPTreeItem_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OrderedData.hpp"
#include "FPTreeItem.hpp"

#define MAX_DOMAIN_ITEMS 1000

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
    int count;
    FPTreeItem *nextFPTreeItem;
    
public:
    FPTreeItem();
    FPTreeItem(int data, int count, FPTreeItem *ptr);
    virtual ~FPTreeItem();
    
    void increment();

    //*****************Minor Methods********************
    int 	compareTo(OrderedData *item);
    int     compareFrequencyTo(FPTreeItem *item);
    void 	print();
    string  toString();
    
    //************ Getters ********
    int getData();
    int getCount();
    FPTreeItem* getNextFPTreeItem();
};

#endif