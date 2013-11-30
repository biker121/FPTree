//
//  FPTree.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTree_hpp
#define _710_Project_FrequentItemMining_FPTree_hpp

#include <string>

#include "HeaderTable.hpp"
#include "FPTreeNode.hpp"
#include "FPTree.hpp"


using namespace std;

class FPTreeNode;

class FPTree {
private:
    HeaderTable *headerTable;
    FPTreeNode *root;
    int minSup;

    void createTree(string fileName);
    void insertTransaction(FPTreeItem *items[], int size);
    void printTree();
    
public :
    FPTree(int minSup);
    virtual ~FPTree();
    
    static void processFile(string fileName, int minSup);
};
#endif
