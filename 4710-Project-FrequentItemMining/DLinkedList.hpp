//
//  DLinkedList.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DLinkedList_hpp
#define _710_Project_FrequentItemMining_DLinkedList_hpp

#include <iostream>
#include "NodeLL.hpp"
#include "OrderedData.hpp"

class DLinkedList {
  
private:
    NodeLL *head;
    NodeLL *tail;
    int size;
    
    
public:
    DLinkedList();
    ~DLinkedList();
    
    NodeLL *find(OrderedData *target);

    NodeLL *addToFront(OrderedData *item);
    NodeLL *addToBack(OrderedData *item);
    void remove(OrderedData *target);
    
    int getSize();
    OrderedData* getData(int index);
    
    void print();
};

#endif
