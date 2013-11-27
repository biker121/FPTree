//
//  FPTreeItem.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderTable.hpp"
#include "FPTreeItem.hpp"

//------------------Constructor/Destructor---------------------
FPTreeItem::FPTreeItem(){
	this->data = 0;
	this->count = 0;
    this->nextFPTreeItem = NULL;
}

FPTreeItem::FPTreeItem(int data, int count, FPTreeItem *ptr){
	this->data = data;
	this->count = count;
    this->nextFPTreeItem = ptr;
}

FPTreeItem::~FPTreeItem(){}
//-------------------------------------------------------------

void FPTreeItem::increment(){
    this->count++;
}

/*----------------------------------------------------------------------------------------
 * @purpose: compares based on data value itself and returns an integer representing result of comparison
 * @parm   : OrderedData *, item that is to be compared
 * @return : 0 -> if both FPTreeItems have same data value
 *         :+1 -> current tree would appear after  the given, in a sorted order
 *         :-1 -> current tree swould appear before the given, in a sorted order
 *----------------------------------------------------------------------------==----------
 */
int FPTreeItem::compareTo(OrderedData *item){
	FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(item);
	int result;
    
	if (otherFPTreeItem == NULL){
		cout << "Error: class conflict <-FPTreeItem::compareTo(OrderedData *)" << endl;
		result = -1;
	} else {
        
        if (this->data < otherFPTreeItem->data)
            result = -1;
        else if (this->data == otherFPTreeItem->data)
            result = 0;
        else
            result = 1;
 	}
    
	return result;
}


//@purpose: Compares based on frequency
int FPTreeItem::compareFrequencyTo(FPTreeItem *item){
    int result = 0;
    
    if (item != NULL)
        result = this->count - item->count;
    
    return result;
}

/*-----------------------print()---------------------------------------------
 * @purpose: prints data item and count
 *---------------------------------------------------------------------------
 */
void FPTreeItem::print(){
	cout << this->data << "[" << this->count << "]" << endl;
}

string FPTreeItem::toString(){
    stringstream ss;
    ss << this->data << "[" << this->count << "]";

    return ss.str();
}

//************** GETTERS ***********************
int FPTreeItem::getData(){ return this->data; }
int FPTreeItem::getCount(){ return this->count; }
FPTreeItem* FPTreeItem::getNextFPTreeItem(){ return this->nextFPTreeItem; }