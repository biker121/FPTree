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

// private helper method for findFreqItems()
void getPrefix(int i, string &str, string &result)
{
    int count = 0;
    size_t pos = 0;
    size_t newPos = 0;
    std::string token;
    while ((newPos = str.find(',', pos)) != std::string::npos && count < i)
    {
        token = str.substr(pos, newPos-pos);
        pos=newPos+1;
        if(count == 0)
            result += token;
        else
            result += "," + token;
        
        count++;
    }
}

// finds all the permutations of a given single path items
void findFreqItems(int k, vector<string> *items)
{
    vector<string> *fitems = new vector<string>;
    
    if(k==1)
    {
        for(int i=0; i<items->size(); i++)
        {
            string curri = items->at(i);
            for (int j=i+1; j<items->size(); j++) {
                string currj = items->at(j);
                string joint = curri + "," + currj;
                fitems->push_back(joint);
                
//                // DEBUG Print K-2 items
//                cout << "fitem: " <<  joint << endl;
            }
        }
        
    }if(k>1) {
        for(int i=0; i<items->size(); i++)
        {
            string curri = items->at(i);
            string prefix;
            
            getPrefix(k-1, curri, prefix);
            
            int j = i+1;
            bool matches = true;
            while(matches && j<items->size())
            {
                string currj = items->at(j);
                string currjPrefix;
                getPrefix(k-1, currj, currjPrefix);
                
                if(prefix.compare(currjPrefix)==0)
                {
                    string joint = curri + "," + currj.substr(currjPrefix.length() + 1);
                    fitems->push_back(joint);
                
//                    // DEBUG Print K>2 items
//                    cout << "-->fitem: " <<  joint << endl;
                }else
                {
                    matches = false;
                }
                
                j++;
            }
        }
    }
    
    if(fitems->size()>1)
    {
        findFreqItems(k+1, fitems);
    }
}

void FPGrowthMine(FPTree* tree, int base)
{
	HeaderTable *headerTable = tree->getHeaderTable();
	
	// Iterates through each header item in the header table starting from
	// the bottom to the top
	NodeLL *currHeaderNode = dynamic_cast<NodeLL*>(headerTable->getLowestFreqNode());
	while(currHeaderNode != NULL)
	{
        HeaderItem *headerItem = (HeaderItem*)currHeaderNode->getData();
        DLinkedList *paths[headerItem->getSimilarNodeCount()];
        DLinkedList *path = NULL;
        
        FPTree *newProjTree = new FPTree(tree->getMinSup(), headerItem->getData()->getData(), tree);
        HeaderTable *projHeader = newProjTree->getHeaderTable();
        
        int currPathIndex = 0;
        
		// Iterates over nodes in the FP tree starting with a given header item
		// and generates a new list containing that path following the global
		// FP tree sorting order
		FPTreeNode *currSimilarNode = headerItem->getFirstSimilarTreeNode();
		while(currSimilarNode != NULL)
		{
            paths[currPathIndex] = new DLinkedList();
            path = paths[currPathIndex];
            
            int currNodeSupport = currSimilarNode->getData()->getSupport();
            
			// generates a path by chasing the parent pointers
			FPTreeNode *parent = currSimilarNode->getParent();
			while(parent->getData()!=NULL)
			{
                FPTreeItem *dataItem = parent->getData();
                FPTreeItem *item = new FPTreeItem(dataItem->getData(), currNodeSupport);
                TransPathItem *pathItem = new TransPathItem(item, paths[currPathIndex]);
                NodeLL* addedPathNode = paths[currPathIndex]->addToFront(pathItem);
                
                // add to header table
				HeaderItem *hItem = projHeader->insertByFreqOrder(dataItem->getData(), currNodeSupport);
                hItem->linkNextPath(addedPathNode);
                
				parent = parent->getParent();
			}// end - path generate loop
            
			currPathIndex++;
            
			currSimilarNode = currSimilarNode->getNextSimilarNode();
            
		} // end - all paths generation loop
        
//        // DEBUG Print
//        cout << "Item: " << headerItem->getData()->getData() << "\n";
//        projHeader->printTable();
//
//        // DEBUG Print
//        cout << "paths before pruning:\n";
//        for (int i=0; i<headerItem->getSimilarNodeCount(); i++) {
//            cout << "Path[" << i << "]\n";
//            paths[i]->print();
//        }
        
        // this removes all the infrequent items from the header table
        // while also filtering out the infrequents from the paths
        projHeader->removeInfrequent();
        
//        // DEBUG Print
//        cout << "paths after pruning:\n";
//        for (int i=0; i<headerItem->getSimilarNodeCount(); i++) {
//            cout << "Path[" << i << "]\n";
//            paths[i]->print();
//        }
        
		//insert all paths and DELETE them
        for (int i=0; i<headerItem->getSimilarNodeCount(); i++)
        {
            newProjTree->insertTransaction(paths[i]);
            
            // also DELETE paths because we dont need them anymore
            delete paths[i];
        }
        
        
//        // DEBUG Print
//        if(!newProjTree->isEmpty() && base==0)
//        {
//            cout << "Item: ";
//            headerItem->print();
//            newProjTree->printTree();
//            cout << "\n";
//        }
        
        if(newProjTree->isEmpty() || newProjTree->isSinglePath())
        {
//            // DEBUG Print
//            cout << "Item: ";
//            headerItem->print();
            vector<string> *singletons = newProjTree->getSinglePath();
            findFreqItems(1, singletons);
        }else
        {
            FPGrowthMine(newProjTree, base+1);
        }
        
        // going backwards from lowest to highest order
        currHeaderNode = currHeaderNode->getPrev();
	}
}
                          
/*-----------------------------------------------------------------------------------
 * PURPOSE : primary handler method for mining a given datafile with indicated minsup
 * PARM    : string fileName, absolute file name
 * PARM    : int minSup, support threshold for frequent items
 *----------------------------------------------------------------------------------*/
FPTree* processFile(string fileName, int minSup)
{
    HeaderItem **hash =  new HeaderItem *[MAX_DOMAIN_ITEMS];
    FPTree *tree = new FPTree(minSup);
    
    //first pass - populate frequent items
    tree->createHeaderTable(fileName, hash); //will also fill hash[] with frequent 1-itemsets
    tree->printHeaderTable();
    
    //second pass - tree creation of frequent items
    if (tree->getHeaderTable()->getNumDomainItem() > 0) {
        tree->createTree(fileName, hash);
        tree->printTree();
        
        delete[] hash; //DEBUG - double check**
    }
    
    return tree;
}

int main(int argc, const char * argv[])
{    
    if (argc == 3)
    {
        string fileName = argv[1];
        int minSup = atoi(argv[2]);
        
        minSup = 2;
        
        cout << "===== FP-growth TDB=" << fileName << " minsup=" << minSup << " =====" << endl;
        FPTree* globalTree = processFile(fileName, minSup); //read, create, and mine tree
        FPGrowthMine(globalTree, 0);
        cout << "=====================================================================" << endl;
    } else
    {
        cout << "Invalid parameters - must have <filename> <minsup>";
    }
    
    cout << "\nEnd of processing.\n";
    
    return EXIT_SUCCESS;
}
