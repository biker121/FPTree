//
//  HeaderItem.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_HeaderItem_hpp
#define _710_Project_FrequentItemMining_HeaderItem_hpp

#include <string>

#include "OrderedData.hpp"

using namespace std;

class FPTreeNode;

class HeaderItem : public OrderedData {
private:
    //FPTreeItem *item
    FPTreeNode *data; //refactor - pointer to node in tree
    int priority; //refactor - remove --> compare FPTreeItem *item instead

public:
    HeaderItem(FPTreeNode *data);
    ~HeaderItem();
    
    int compareTo(OrderedData *other); //--refactor -
    void print();
    
    //************* GETTERS *************
    FPTreeNode* getNode();
    int getPriority();
    
    //************* SETTERS *************
    void setPriority(int priority);
};

#endif