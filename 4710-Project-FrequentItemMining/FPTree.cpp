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
void FPTree::insertTransaction(FPTreeItem *items[], int size)
{
    this->headerTable->prioritizeItems(items, size);
    this->root->insertTransaction(items, size, 0, this->headerTable);
}

HeaderTable* FPTree::createHeaderTable(string fileName)
{
    headerTable->createHeaderTable(fileName);
    return headerTable;
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

//**************************** GETTERS ************************
int FPTree::getMinSup()
{
    return this->minSup;
}

HeaderTable* FPTree::getHeaderTable()
{
    return headerTable;
}