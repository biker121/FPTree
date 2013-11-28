//
//  FPTree.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTree.hpp"

//------------------------Constructors and destructors-----------------------
FPTree::FPTree(){
    this->headerTable = new HeaderTable();
    this->root = new FPTreeNode();
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
    FPTree *tree = new FPTree();
    
    //first pass - frequency population
    tree->headerTable->createHeaderTable(fileName, minSup);
    tree->headerTable->printTable();

    //second pass - tree creation
    tree->createTree(fileName);
    
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
    int temp;
    
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
                for (int i=0; i<transactionSize; i++){
                    dataFile >> temp;
                    buffer[i] = new FPTreeItem(temp, 1); //temp is later freed
                }
                
                //insert transaction
                this->insertTransaction(buffer, transactionSize);
                
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
    }
    
}

// @purpose : passes job to root node which recursively inserts each item
void FPTree::insertTransaction(FPTreeItem *items[], int size){
//    HeaderTable::prioritizeItems(items, size);
//    this->root->insertTransaction(items, size, 0);
}

void FPTree::printTree(){
    this->root->print(0);
}