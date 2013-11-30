//
//  FPTree.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTree.hpp"

//------------------------Constructors and destructors-----------------------
FPTree::FPTree(int minSup){
    this->headerTable = new HeaderTable(minSup);
    this->root = new FPTreeNode();
    this->minSup = minSup;
}
FPTree::~FPTree(){
    delete(headerTable);
    delete(root);
}//--------------------------------------------------------------------------

/*-----------------------------------------------------------------------------------
 * @purpose: primary handler method for mining a given datafile with indicated minsup
 * @parm   : string fileName, absolute file name
 * @parm   : int minSup, support threshold for frequent items
 *-----------------------------------------------------------------------------------
 */
void FPTree::processFile(string fileName, int minSup){
    FPTree *tree = new FPTree(minSup);
    
    //first pass - frequency population
    tree->headerTable->createHeaderTable(fileName);
    tree->headerTable->printTable();

    //second pass - tree creation
    if (tree->headerTable->getNumDomainItem() > 0){
        tree->createTree(fileName);
        tree->printTree();
        
        //DEBUG
        tree->headerTable->verifyFrequencies(); //verifies tree node frequencies with header table frequency 
    }
    
    //third pass - data mining
    
    
    //free objects
    delete(tree);
}

// @purpose : creates the FP-Tree by inserting one transaction at a time
void FPTree::createTree(string fileName){
    ifstream dataFile;
    int numTransactions;
    int currTransaction, transactionSize;
    
    FPTreeItem *buffer[MAX_DOMAIN_ITEMS];
    FPTreeItem *tempItem;
    int temp;
    int bufferIndex;
    
    dataFile.open(fileName.c_str());
    
    if ( dataFile.is_open() == false ){
        cout<<"Error while opening file. "<< endl;
    } else {
        dataFile >> numTransactions;
        
        //cycle through each transaction
        if (numTransactions > 0){
            do {
                dataFile >> currTransaction >> transactionSize;
                
                //read entire transaction into array
                bufferIndex = 0;
                for (int i=0; i<transactionSize; i++){
                    dataFile >> temp;
                    tempItem = new FPTreeItem(temp, 1); //temp is later freed
                    
                    if (this->headerTable->isFrequent(tempItem) == true){
                        buffer[bufferIndex] = tempItem;
                        bufferIndex++;
                    } else {
                        delete(tempItem);
                        tempItem = NULL;
                    }
                }
                
                //insert transaction
                this->insertTransaction(buffer, bufferIndex);
                
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
    }
    
}

// @purpose : passes job to root node which recursively inserts each item
void FPTree::insertTransaction(FPTreeItem *items[], int size){
    this->headerTable->prioritizeItems(items, size);
    this->root->insertTransaction(items, size, 0, this->headerTable);
}

void FPTree::printTree(){
    this->root->print(0);
}