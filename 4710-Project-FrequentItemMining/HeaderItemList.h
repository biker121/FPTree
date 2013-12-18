//
//  HeaderItemList.h
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-17.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef ___710_Project_FrequentItemMining__HeaderItemList__
#define ___710_Project_FrequentItemMining__HeaderItemList__

#include <iostream>
#include "NodeLL.hpp"
#include "HeaderItem.hpp"

class HeaderItem;

class HeaderItemList
{
private:
    NodeLL* head;
    NodeLL* tail;
    
public:
    HeaderItemList();
    ~HeaderItemList();
    
    HeaderItem* insertByFreqOrder(HeaderItem* item);
    void orderedInsert(HeaderItem* item);
    void print();
    
    NodeLL* getHeadNode();
    NodeLL* getTailNode();
};
#endif
