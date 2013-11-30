//
//  HeaderItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"
#include "HeaderItem.hpp"
#include "HeaderTable.hpp"

HeaderItem::HeaderItem(FPTreeNode *data){
    this->data = data;
    this->priority = 0;
}
HeaderItem::~HeaderItem(){
    delete(data);
}

// @purpose : compares the frequency of two HeaderItems.
// @remark  : NULL item is automatically assigned 0 priority
int HeaderItem::compareTo(OrderedData *other){
    HeaderItem *otherItem = NULL;
    int result = 1;
    
    if (other != NULL && (otherItem = dynamic_cast<HeaderItem *>(other)) != NULL)
        result = this->getData()->getData()->compareTo(otherItem->getData()->getData());
    
    return result;
}

// @purpose : prints priority, data value, frequency (e.g. "{10} 22 : 1")
void HeaderItem::print(){
    cout << "{" << this->priority << "} ";
    this->data->print();
    cout << endl;
}

//***************** GETTERS ******************
int HeaderItem::getPriority(){ return this->priority; }
FPTreeNode* HeaderItem::getData(){ return this->data; }

//***************** SETTERS ******************
void HeaderItem::setPriority(int priority){
    this->priority = priority;
}