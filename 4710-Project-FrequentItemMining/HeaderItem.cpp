//
//  HeaderItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTreeNode.hpp"

#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"
#include "HeaderItem.hpp"
#include "HeaderTable.hpp"

//------------------------Constructors and destructors-----------------------
HeaderItem::HeaderItem(FPTreeNode *data){
    this->data = data;
    this->priority = 0;
}
HeaderItem::~HeaderItem(){
    delete(data);
}//--------------------------------------------------------------------------

// @purpose : compares the frequency of two HeaderItems
// @parm    : HeaderItem - item that is being compared
// @return  : <0 = 'this' item is less frequent
//          : 0  = same frequency
//          : >0 = 'this' item is more frequent
// @remark  : NULL items are taken as lowest priority
int HeaderItem::compareTo(OrderedData *other){
    HeaderItem *otherItem = NULL;
    int result = 1;
    
    if (other != NULL && (otherItem = dynamic_cast<HeaderItem *>(other)) != NULL)
        result = this->getNode()->getData()->compareTo(otherItem->getNode()->getData());
    
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
FPTreeNode* HeaderItem::getNode(){ return this->data; }

//***************** SETTERS ******************
void HeaderItem::setPriority(int priority){
    this->priority = priority;
}