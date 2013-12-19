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
#include <vector>

#include "FPTree.hpp"
#include "FPTreeNode.hpp"
#include "FPTreeItem.hpp"
#include "HeaderTable.hpp"
#include "HeaderItem.hpp"
#include "DLinkedList.hpp"
#include "TransPathItem.hpp"
#include "NodeLL.hpp"

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

void FPGrowthMine(FPTree* tree, int base)
{
	HeaderTable *headerTable = tree->getHeaderTable();
	
	// Iterates through each header item in the header table starting from
	// the bottom to the top
	NodeLL *currHeaderNode = dynamic_cast<NodeLL*>(headerTable->getLowestFreqNode());
	while(currHeaderNode != NULL)
	{
        FPTree *newProjTree = new FPTree(tree->getMinSup());
        HeaderItem *headerItem = dynamic_cast<HeaderItem*>(currHeaderNode->getData());
        DLinkedList *paths[headerItem->getSimilarNodeCount()];
        HeaderTable *projHeader = newProjTree->getHeaderTable();
        
        int currPathIndex = 0;
        
		// Iterates over nodes in the FP tree starting with a given header item
		// and generates a new list containing that path following the global
		// FP tree sorting order
		FPTreeNode *currSimilarNode = headerItem->getFirstSimilarTreeNode();
		while(currSimilarNode != NULL)
		{
            paths[currPathIndex] = new DLinkedList();
            
			// generates a path by chasing the parent pointers
			FPTreeNode *parent = currSimilarNode->getParent();
			while(parent!=NULL)
			{
				FPTreeNode *parent = currSimilarNode->getParent();
                FPTreeItem *dataItem = parent->getData();
                
                FPTreeItem *item = new FPTreeItem(dataItem->getData(), dataItem->getSupport());
                TransPathItem *pathItem = new TransPathItem(item, NULL);
                NodeLL* addedPathNode = paths[currPathIndex]->addToFront(pathItem);
                
                // add to header table
				HeaderItem *hItem = projHeader->insertByFreqOrder(dataItem->getData());
                hItem->linkNextPath(addedPathNode);
                
				parent = parent->getParent();
			}
            
			currPathIndex++;
            
			currSimilarNode = currSimilarNode->getNextSimilarNode();
		}
        
		//insert all paths
        currHeaderNode = currHeaderNode->getPrev();
	}
}

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
