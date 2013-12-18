//
//  NodeLL.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_NodeLL_hpp
#define _710_Project_FrequentItemMining_NodeLL_hpp


#include <iostream>

class OrderedData;

class NodeLL {
    
private:
    OrderedData *data;
    NodeLL *prev;
    NodeLL *next;
    
public:
    NodeLL(OrderedData *data, NodeLL *prev, NodeLL *next);
    NodeLL(OrderedData *data);
    ~NodeLL();
    
    void print();
    
    OrderedData *getData();
    NodeLL *getPrev();
    NodeLL *getNext();
    
    void setData(OrderedData *data);
    void setPrev(NodeLL *prev);
    void setNext(NodeLL *next);
};


#endif
