//
//  FPTreeItem.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTreeItem_hpp
#define _710_Project_FrequentItemMining_FPTreeItem_hpp

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OrderedData.hpp"
#include "FPTreeItem.hpp"

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
    void increaseSupport(FPTreeItem *item);
        
    //*****************Minor Methods********************
    int 	compareTo(OrderedData *item);       //compares frequency
    void 	print();
    bool    isEqualsTo(OrderedData *target);    //compares data value
    
    //************ Getters ********
    int getData();
    int getSupport();
};

#endif