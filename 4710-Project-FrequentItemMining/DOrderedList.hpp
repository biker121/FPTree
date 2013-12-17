//
//  DOrderedList.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DOrderedList_hpp
#define _710_Project_FrequentItemMining_DOrderedList_hpp

#include <cstdlib>

using namespace std;

class DLinkedList;
class OrderedData;
class NodeLL;

class DOrderedList {
    
private:
    DLinkedList *list;
    int size;
    
    NodeLL *find(OrderedData *target);

public:
    DOrderedList();
    ~DOrderedList();
    
    bool insert(OrderedData *item);
    
    OrderedData* remove(OrderedData *target);
    void destory(OrderedData *target);
    
    int getSize();
    void print();
    
    NodeLL* getHead();
};

#endif
