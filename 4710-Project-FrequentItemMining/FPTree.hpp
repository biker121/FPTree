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

using namespace std;

class HeaderTable;
class FPTreeNode;
class FPTreeItem;

class FPTree
{
private:
    HeaderTable *headerTable;
    FPTreeNode *root;
    int partialLabel;
    FPTree *parentProj;
    
    int minSup;
    void printTree();
    
public :
    FPTree(int minSup);
    virtual ~FPTree();

    void insertTransaction(FPTreeItem *items[], int size);
    HeaderTable* createHeaderTable(string fileName);
    void printHeaderTable();
    
    int getMinSup();
    HeaderTable* getHeaderTable();
};
#endif