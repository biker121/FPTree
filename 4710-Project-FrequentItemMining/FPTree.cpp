//
//  FPTree.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "FPTree.hpp"

/*-----------------------processFile(string, int)-------------------------------------------
 * @purpose: primary handler method for mining a given datafile with indicated minsup
 * @parm   : string fileName, absolute file name
 * @parm   : int minSup, support threshold for frequent items
 *--------------------------------------------------------------------------------------
 */
void FPTree::processFile(string fileName, int minSup){
    HeaderTable *headerTable = new HeaderTable();
    
    headerTable->createHeaderTable(fileName, minSup);
    headerTable->printTable();
    
    delete headerTable;
    
    cout << "test\n";
}