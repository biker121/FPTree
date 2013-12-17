//
//  main.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "test.h"

#include <string>
#include <iostream>

#include "FPTree.hpp"
#include "FPTreeItem.hpp"
#include "HeaderTable.hpp"

using namespace std;
//-----------------------------------------------------------
// AUTHOR(S)	  :	Brahmdeep Singh Juneja, Sukhpreet Lotey
// COURSE		  : Comp 4710 - Data Mining
// INSTRUCTOR	  : Carson K. Leung
//
// REMARKS        : This implementation of an FP-Tree algorithm to mine data
//                  from a given data set.
//
//-----------------------------------------------------------

void fp_groth_mine(FPTree* tree, int base)
{
    
	HeaderTable *headerTable = tree->getHeaderTable();
	
	// Iterates through each header item in the header table starting from
	// the bottom to the top
	HeaderItem *currHeaderItem = headerTable->get_lowest_freq_item();
	while(currHeaderItem->prev()!=NULL)
	{
		DLinkedList *paths = new DLinkedList();
        
		// Iterates over nodes in the FP tree starting with a given header item
		// and generates a new list containing that path following the global
		// FP tree sorting order
		FPTreeNode *currNode = currHeaderItem->getNode();
		while(currNode!=null)
		{
			// generates a path by chasing the parent pointers
			FPTreeNode *parent = currNode->getParent();
			while(parent!=NULL)
			{
				FPTreeNode *parent = currNode->getParent();
                FPTreeItem *dataItem = parent->getData();
				
				// add to header table
				projHeaderTable->addByFreqOrder(dataItem->getData());
                
				// add to paths
				??curr_path->addToFront(new FPTreeItem(dataItem->getData(),
													   dataItem->getFrequency()));
                
				parent = parent->getParent();
			}
            
			// create a new node for path
			paths->add(curr_path);
            
			currNode = currNode->getNextSimilarNode();
		}
        
		curr = curr->prev();
	}
}

/*-----------------------------------------------------------------------------------
 * PURPOSE: creates the FP-Tree by reading and inserting one transaction at a time for
 *          only the frequent items
 *----------------------------------------------------------------------------------*/
void createTree(FPTree* tree, string fileName, FPTreeItem *hash[MAX_DOMAIN_ITEMS])
{
    ifstream dataFile;
    int numTransactions;
    int currTransaction, transactionSize;
    
//    FPTreeItem *buffer[MAX_DOMAIN_ITEMS];
    FPTreeItem *tempItem;
    int temp;
//    int bufferIndex;
    
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
                    
                    /*
                     * -- refactor - add to ordered list instead of array
                        - insert based on its priorty in hash
                     */
                    int index = HeaderTable::getHashIndex(tempItem);
                    
                    if (hash[index] != NULL) {
                        //insert *tempItem
                    } else {
                        delete(tempItem);
                        tempItem = NULL;
                    }
                    
//                    if (tree->getHeaderTable()->isFrequent(tempItem) == true){
//                        buffer[bufferIndex] = tempItem;
//                        bufferIndex++;
//                    } else {
//                        delete(tempItem);
//                        tempItem = NULL;
//                    }
                }
                
                //insert transaction
                tree->insertTransaction(buffer, bufferIndex); //modify to accept list
                //delete list
                
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
    }
}

/*-----------------------------------------------------------------------------------
 * @purpose: primary handler method for mining a given datafile with indicated minsup
 * @parm   : string fileName, absolute file name
 * @parm   : int minSup, support threshold for frequent items
 *----------------------------------------------------------------------------------*/
void processFile(string fileName, int minSup)
{
    FPTree *tree = new FPTree(minSup);
    HeaderItem *hash[MAX_DOMAIN_ITEMS];
    
    //first pass - frequency population
    tree->createHeaderTable(fileName, hash); //will fill hash[] with frequent 1-itemsets
    tree->printHeaderTable();
    
    //second pass - tree creation
    if (tree->getHeaderTable()->getNumDomainItem() > 0) {
        createTree(tree, fileName, hash);
        //tree->printTree();
        
        //DEBUG
        tree->getHeaderTable()->verifyFrequencies(); //verifies tree node frequencies with header table frequency
    }
    
    //third pass - data mining
    
    //free objects
    delete(tree);
}

/*-------------------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * PARM   :
 * RETURN :
 * REMARKS:
 *-----------------------------------------------------------------------------------*/
int main(int argc, const char * argv[])
{
    run_tests();
    
    if (argc == 3) {
        string fileName = argv[1];
        int minSup = atoi(argv[2]);
        
        //*** test use only ***
        minSup = 2;
        
        cout << "===== FP-growth TDB=" << fileName << " minsup=" << minSup << " =====" << endl;
        processFile(fileName, minSup);
        cout << "=====================================================================" << endl;
    } else {
        cout << "Invalid parameters - must have <filename> <minsup>";
    }
    
    cout << "\nEnd of processing.\n";
    
    return EXIT_SUCCESS;
}

