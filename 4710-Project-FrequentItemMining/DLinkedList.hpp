//
//  DLinkedList.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DLinkedList_hpp
#define _710_Project_FrequentItemMining_DLinkedList_hpp

#include <cstdlib>

using namespace std;

class NodeLL;
class Data;

class DLinkedList {
  
private:
    NodeLL *head;
    NodeLL *tail;
    int size;
    
    NodeLL *find(Data *target);

public:
    DLinkedList();
    ~DLinkedList();
    
    //    Data* getData(int index);

    bool addToFront(Data *item);
    bool addToBack(Data *item);
    
    Data* remove(Data *target);
    void destroy(Data *target);
    
    void print();

    //************ Getters ********
    NodeLL* getHead();
    NodeLL* getTail();
    int getSize();

    //************ Setters ********
    void setHead(NodeLL *head);
    void setTail(NodeLL *tail);
    void setSize(int size);
};

#endif
