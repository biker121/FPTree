//
//  DLinkedList.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DLinkedList_hpp
#define _710_Project_FrequentItemMining_DLinkedList_hpp

class NodeLL;
class Data;

class DLinkedList {
  
private:
    NodeLL *head;
    NodeLL *tail;
    int size;
    
    
public:
    DLinkedList();
    ~DLinkedList();
    
    NodeLL *find(Data *target);

    bool addToFront(Data *item);
    bool addToBack(Data *item);
    void remove(Data *target);
    
    void print();
};

#endif
