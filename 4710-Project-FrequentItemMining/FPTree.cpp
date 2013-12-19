//
//  FPTree.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTree.hpp"

#include <iostream>
#include <string>
#include <fstream>

#include "FPContants.hpp"

#include "DLinkedList.hpp"
#include "FPTreeNode.hpp"
#include "HeaderItem.hpp"
#include "FPTreeItem.hpp"
#include "HeaderTable.hpp"

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
}//-------------------------------------------------------------------------

/*-----------------------------------------------------------------------------------
 * PURPOSE : primary handler method for mining a given datafile with indicated minsup
 * PARM    : string fileName, absolute file name
 * PARM    : int minSup, support threshold for frequent items
 *----------------------------------------------------------------------------------*/
void FPTree::processFile(string fileName, int minSup)
{
    HeaderItem **hash =  new HeaderItem *[MAX_DOMAIN_ITEMS];
    FPTree *tree = new FPTree(minSup);
    
    //first pass - populate frequent items
    tree->createHeaderTable(fileName, hash); //will also fill hash[] with frequent 1-itemsets
    tree->printHeaderTable();
    
    //second pass - tree creation of frequent items
    if (tree->getHeaderTable()->getNumDomainItem() > 0) {
        tree->createTree(fileName, hash);
        //tree->printTree();
        
        delete[] hash; //DEBUG - double check**
        
        //third pass - data mining
        //        tree->mine();
    }
    
    //free objects
    delete(tree);
}

/*-----------------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * PARM   :
 * RETURN :
 * REMARKS:
 *----------------------------------------------------------------------------------*/
void FPTree::createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    this->headerTable->createHeaderTable(fileName, hash);
}

/*-----------------------------------------------------------------------------------
 * PURPOSE: creates the FP-Tree by reading and inserting one transaction at a time for
 *          only the frequent items
 *----------------------------------------------------------------------------------*/
void FPTree::createTree(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    ifstream dataFile;
    int numTransactions;
    int currTransaction, transactionSize;
    
    FPTreeItem **buffer =  new FPTreeItem *[MAX_DOMAIN_ITEMS];
    int size; //buffer size
    
    FPTreeItem *tempItem;
    int temp;
    int hashIdx;
    
    dataFile.open(fileName.c_str());
    
    if ( dataFile.is_open() == false )
    {
        cout<<"Error while opening file. "<< endl;
    } else
    {
        dataFile >> numTransactions;
        
        //cycle through each transaction
        if (numTransactions > 0)
        {
            do {
                dataFile >> currTransaction >> transactionSize;
                size = 0;
                
                //read entire transaction into array
                for (int i=0; i<transactionSize; i++)
                {
                    dataFile >> temp;
                    tempItem = new FPTreeItem(temp, 1); //temp is later freed
                    
                    hashIdx = HeaderTable::getHashIndex(tempItem);
                    if (hash[hashIdx] != NULL)
                    { //if frequent
                        buffer[size] = tempItem;
                        size++;
                    } else
                    {
                        delete(tempItem);
                        tempItem = NULL;
                    }
                }
                FPTree::sortByPriority(buffer, size, hash);
                
                //DEBUG
//                cout << "----new transaction ----" << endl;
//                for (int i=0; i<size; i++){
//                    if (buffer[i] != NULL){
//                        buffer[i]->print();
//                        cout << endl;
//                    }
//                }
//                cout << endl;
                
                this->insertTransaction(buffer, size, hash);
//                this->printTree(); //DEBUG
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
    }
    delete[] buffer;
}

// PURPOSE: sorts **array based by comparing their counterparts in the **hash, in descending order
void FPTree::sortByPriority(FPTreeItem **array, int size, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    FPTreeItem *temp;
    int tempIdx;
    int j;
    
    for (int i=0; i<size; i++)
    {
        tempIdx = HeaderTable::getHashIndex(array[i]);
        
        if (hash[tempIdx] == NULL)
        {
            delete(array[i]);
            array[i] = NULL;
        } else
        {
            temp = array[i];
            for (j=i; j>0 && ((array[j-1] == NULL) || (hash[tempIdx]->compareTo(hash[HeaderTable::getHashIndex(array[j-1])]) > 0)); j--)
            {
                array[j] = array[j-1];
            }
            array[j] = temp;
        }
    }
}

/*----------------------------------------------------------------------------
 * PURPOSE: passes job to root node which recursively inserts each item
 * PARM   : buffer - items to be inserted into tree
 * PARM   : size - buffer size
 * PARM   : hash - passed for deleting consumed items to avoid dangling ptrs
 * REMARKS: - inserts all items from the array
 *          - any item from items[] that are not used, are freed
 *--------------------------------------------------------------------------*/
void FPTree::insertTransaction(FPTreeItem *buffer[MAX_DOMAIN_ITEMS], int size, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    if (size > 0)
    {
        this->root->insertTransaction(buffer, size, hash);
    }
}

/*----------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * PARM   :
 * REMARKS: - frees data items from transactionItems list
 *--------------------------------------------------------------------------*/
void FPTree::insertTransaction(DLinkedList *transactionItems, HeaderItem *hash[MAX_DOMAIN_ITEMS])
{
    if (transactionItems->getSize() > 0)
    {
        this->root->insertTransaction(transactionItems, hash);
    }
}

/*----------------------------------------------------------------------------
 * PURPOSE: prints the tree structure to console by recursively calling print node
 *--------------------------------------------------------------------------*/
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
    while (currProj != NULL && currProj->partialPrefix != -1)
    {
        ss << this->partialPrefix;
        currProj = currProj->parentProj;
    }
    
    return ss.str();
}

// PURPOSE: returns integer representing base k-level projection
int FPTree::getBaseLevel()
{
    int lvl = 0;
    FPTree *currProj = this;
    
    while (currProj != NULL && currProj->partialPrefix != -1)
    {
        lvl++;
        currProj = currProj->parentProj;
    }
    
    return lvl;
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