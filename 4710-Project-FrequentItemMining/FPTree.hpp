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
#include "HeaderTable.cpp"

using namespace std;

class HeaderItem;
class FPTreeNode;
class FPTreeItem;

class FPTree
{
private:
    HeaderTable *headerTable;
    FPTreeNode *root;
    int minSup;
    
    int partialPrefix; //default = -1, indicating intial tree
    FPTree *parentProj; 

    void printTree();
    
public :
    FPTree(int minSup);
    FPTree(int minSup, int partialLabel, FPTree *parentProj);
    virtual ~FPTree();

    void insertTransaction(FPTreeItem *items[], int size);
    void createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void printHeaderTable();
    
    string getLabelPrefix();
    int getBaseLevel();
    
    int getMinSup();
    HeaderTable* getHeaderTable();
};
#endif