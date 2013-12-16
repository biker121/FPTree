//
//  ProjHeaderTable.h
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-15.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef ___710_Project_FrequentItemMining__ProjHeaderTable__
#define ___710_Project_FrequentItemMining__ProjHeaderTable__

#include <iostream>
#include "DLinkedList.hpp"
#include "FPTreeItem.hpp"

class ProjHeaderTable {
  
private:
    NodeLL *head;
    int size;
    int minsup;
    
public:
    ProjHeaderTable(int minsup);
    ~ProjHeaderTable();
    
    void addByFreqOrder(int item);
    void filterInfreq();
};

#endif 