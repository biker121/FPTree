//
//  ProjHeaderTable.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Sukhpreet Lotey on 2013-12-15.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "ProjHeaderTable.h"
#include "NodeLL.hpp"

ProjHeaderTable::ProjHeaderTable(int minsup)
{
    this->head = NULL;
    this->size = 0;
    this->minsup = minsup;
}

ProjHeaderTable::~ProjHeaderTable()
{
    delete (head);
}

void ProjHeaderTable::addByFreqOrder(int item)
{
    NodeLL* newNode = new NodeLL(NULL);
	NodeLL* curr = head;
	NodeLL* prev = NULL;
	bool done = false;
	
    // set pointer to node in the path
    //newNode->setSimilar(pathNode);
    
	if(head == NULL) {
		head = newNode;
	}else {
		while (curr != NULL && !done)
		{
			
			if(((OrderedData*)curr->getData())->compareTo(NULL) <= 0) {
				prev = curr;
				curr = curr->getNext();
			}else {
				done = true;
			}
			
		}// while
		
		newNode->setNext(curr);
		if(prev == NULL)
			head = newNode;
		else
			prev->setNext(newNode);
	}// else
	
	// increment size
	size++;
}

void ProjHeaderTable::filterInfreq()
{
    NodeLL* curr = head;
	NodeLL* prev = NULL;
	bool done = false;
	
	while ((curr != NULL) && !done) {
		if(((OrderedData*)curr->getData())->compareTo(NULL) < 0) {
			prev = curr;
			curr = curr->getNext();
		}else
			done = true;
	}
	
	if(curr != NULL && ((OrderedData*) curr->getData())->compareTo(NULL)==0)
	{
		// found it! now delete
		if(prev == NULL)
			head = curr->getNext();
		else
			prev->setNext(curr->getNext());
		
		delete curr;
		
		// decrement size
		size -= 1;
	}
}