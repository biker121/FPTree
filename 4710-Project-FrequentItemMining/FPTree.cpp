//
//  FPTree.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include <iostream>
#include <string>
#include "FPTreeNode.hpp"
#include "HeaderTable.hpp"
#include "FPTree.hpp"
#include "FPTreeItem.hpp"

//------------------------Constructors and destructors-----------------------
FPTree::FPTree(int minSup)
{
    this->headerTable = new HeaderTable(minSup);
    this->root = new FPTreeNode();
    this->minSup = minSup;
    
    this->partialPrefix = -1;
    this->parentProj = NULL;
}

FPTree::FPTree(int minSup, int partialPrefix, FPTree *parentProj)
{
    this->headerTable = new HeaderTable(minSup);
    this->root = new FPTreeNode();
    this->minSup = minSup;
    
    this->partialPrefix = partialPrefix;
    this->parentProj = parentProj;
}

FPTree::~FPTree()
{
    delete(headerTable);
    delete(root);
}

/*-----------------------------------------------------------------------------------
 * PURPOSE: passes job to root node which recursively inserts each item
 * PARM   : FPTreeItems[] that are to be inserted into the tree
 * PARM   : size of the items array
 * REMARKS: - inserts all items from the array
 *          - any item from items[] that are not used, are freed
 *----------------------------------------------------------------------------------*/
void FPTree::insertTransaction(FPTreeItem *transactionItems[], int size)
{
    this->headerTable->prioritizeItems(transactionItems, size);
    this->root->insertTransaction(transactionItems, size, 0, this->headerTable);
}

/*-----------------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * PARM   :
 * REMARKS:
 *----------------------------------------------------------------------------------*/
void FPTree::createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    this->headerTable->createHeaderTable(fileName, hash);
}

/*-----------------------------------------------------------------------------------
 * PURPOSE: prints the tree structure to console by recursively calling print node
 *----------------------------------------------------------------------------------*/
void FPTree::printTree()
{
    this->root->print(0);
}

void FPTree::printHeaderTable()
{
    this->headerTable->printTable();
}

// PURPOSE: iterate through projections from yourself -> original tree and append label at each projection
string FPTree::getLabelPrefix()
{
    stringstream ss;
    FPTree *currProj = this;
    
    ss << "";
    while (currProj != NULL && currProj->partialPrefix != -1){
        ss << this->partialPrefix;
        currProj = currProj->parentProj;
    }
    
    return ss.str();
}

// PURPOSE: returns integer representing base k-level projection
int FPTree::getBaseLevel(){
    int lvl = 0;
    FPTree *currProj = this;
    
    while (currProj != NULL && currProj->partialPrefix != -1){
        lvl++;
        currProj = currProj->parentProj;
    }
    
    return lvl;
}

//**************************** GETTERS ************************
int FPTree::getMinSup(){ 
    return this->minSup;
}

HeaderTable* FPTree::getHeaderTable()
{
    return headerTable;
}

