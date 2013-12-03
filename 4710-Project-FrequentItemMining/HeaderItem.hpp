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
    FPTreeNode *data;
    int priority;

public:
    HeaderItem(FPTreeNode *data);
    ~HeaderItem();
    
    int compareTo(OrderedData *other);
    void print();
    
    //************* GETTERS *************
    FPTreeNode* getNode();
    int getPriority();
    
    //************* SETTERS *************
    void setPriority(int priority);
};

#endif