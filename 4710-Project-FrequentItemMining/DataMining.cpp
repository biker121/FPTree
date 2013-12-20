//
//  DataMining.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "DataMining.hpp"

#include "FPTree.hpp"

void FPGrowthMine(FPTree* tree, int base)
{
    
}

/*-----------------------------------------------------------------------------------
 * PURPOSE : primary handler method for mining a given datafile with indicated minsup
 * PARM    : string fileName, absolute file name
 * PARM    : int minSup, support threshold for frequent items
 *----------------------------------------------------------------------------------*/
FPTree* DataMining::processFile(string fileName, int minSup)
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
    }
    
    return tree;
}

