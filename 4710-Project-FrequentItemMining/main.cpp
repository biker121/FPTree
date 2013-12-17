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

//void fp_groth_mine(FPTree* tree, int base)
//{
//    
//	HeaderTable *headerTable = tree->getHeaderTable();
//	
//	// Iterates through each header item in the header table starting from
//	// the bottom to the top
//	HeaderItem *currHeaderItem = headerTable->get_lowest_freq_item();
//	while(currHeaderItem->prev()!=NULL)
//	{
//		DLinkedList *paths = new DLinkedList();
//        
//		// Iterates over nodes in the FP tree starting with a given header item
//		// and generates a new list containing that path following the global
//		// FP tree sorting order
//		FPTreeNode *currNode = currHeaderItem->getNode();
//		while(currNode!=null)
//		{
//			// generates a path by chasing the parent pointers
//			FPTreeNode *parent = currNode->getParent();
//			while(parent!=NULL)
//			{
//				FPTreeNode *parent = currNode->getParent();
//                FPTreeItem *dataItem = parent->getData();
//				
//				// add to header table
//				projHeaderTable->addByFreqOrder(dataItem->getData());
//                
//				// add to paths
//				??curr_path->addToFront(new FPTreeItem(dataItem->getData(),
//													   dataItem->getFrequency()));
//                
//				parent = parent->getParent();
//			}
//            
//			// create a new node for path
//			paths->add(curr_path);
//            
//			currNode = currNode->getNextSimilarNode();
//		}
//        
//		curr = curr->prev();
//	}
//}

/*-------------------------------------------------------------------------------------
 * PURPOSE:
 * PARM   :
 * PARM   :
 * RETURN :
 * REMARKS:
 *-----------------------------------------------------------------------------------*/
int main(int argc, const char * argv[])
{
//    run_tests();
    
    if (argc == 3) {
        string fileName = argv[1];
        int minSup = atoi(argv[2]);
        
        //*** test use only ***
        minSup = 1;
        
        cout << "===== FP-growth TDB=" << fileName << " minsup=" << minSup << " =====" << endl;
        FPTree::processFile(fileName, minSup); //read, create, and mine tree
        cout << "=====================================================================" << endl;
    } else {
        cout << "Invalid parameters - must have <filename> <minsup>";
    }
    
    cout << "\nEnd of processing.\n";
    
    return EXIT_SUCCESS;
}