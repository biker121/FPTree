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

/*-------------------------------------------------------------------------------------
 * PURPOSE: increases the frequency by one
 *-----------------------------------------------------------------------------------*/
void FPTreeItem::increment(){
    this->frequency++;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: compares based on frequency and returns an integer representing result of 
 *          comparison
 * PARM   : OrderedItem *, item that is to be compared
 * PARM   : 0  -> if both FPTreeItems have same data value
 *        : +1 -> this TreeItem would appear after  the given, in alphabetical order
 *        : -1 -> this TreeItem swould appear before the given, in alphabetical order
 *-----------------------------------------------------------------------------------*/
int FPTreeItem::compareTo(OrderedData *item){
	FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(item);
    int result = 0;
    
    if (otherFPTreeItem != NULL)
        result = this->frequency - otherFPTreeItem->frequency;
    
    return result;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: prints data item and frequency
 *-----------------------------------------------------------------------------------*/
void FPTreeItem::print(){
	cout << this->data << " : " << this->frequency;
}

bool FPTreeItem::isEqualsTo(Data *target){
    FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(target);
    bool isEquals = false;
    
    if (otherFPTreeItem != NULL && this->data == otherFPTreeItem->data)
        isEquals = true;
    
    return isEquals;
}

//************** GETTERS ***********************
int FPTreeItem::getData(){ return this->data; }
int FPTreeItem::getFrequency(){ return this->frequency; }