//
//  NodeLL.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_NodeLL_hpp
#define _710_Project_FrequentItemMining_NodeLL_hpp

class Data;

class NodeLL {
    
private:
    Data *data;
    NodeLL *prev;
    NodeLL *next;
    
public:
    NodeLL(Data *data, NodeLL *prev, NodeLL *next);
    ~NodeLL();
    
    void print();
    
    Data *getData();
    NodeLL *getPrev();
    NodeLL *getNext();
    
    void setData(Data *data);
    void setPrev(NodeLL *prev);
    void setNext(NodeLL *next);
};


#endif
