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
	this->frequency = 0;
}

FPTreeItem::FPTreeItem(int data, int frequency){
	this->data = data;
	this->frequency = frequency;
}

FPTreeItem::~FPTreeItem(){}
//-------------------------------------------------------------

void FPTreeItem::increment(){
    this->frequency++;
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
    int result = 0;
    
    if (otherFPTreeItem != NULL)
        result = this->frequency - otherFPTreeItem->frequency;
    
    return result;
}

/*-----------------------print()---------------------------------------------
 * @purpose: prints data item and frequency
 *---------------------------------------------------------------------------
 */
void FPTreeItem::print(){
	cout << this->data << " : " << this->frequency;
}

//************** GETTERS ***********************
int FPTreeItem::getData(){ return this->data; }
int FPTreeItem::getFrequency(){ return this->frequency; }