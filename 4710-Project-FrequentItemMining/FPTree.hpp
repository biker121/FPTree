//
//  FPTree.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/26/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTree_hpp
#define _710_Project_FrequentItemMining_FPTree_hpp

#include <cstdlib>
#include <string>
#include "HeaderTable.hpp"
#include "DLinkedList.hpp"

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
    
    static void sortByPriority(FPTreeItem **array, int size, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    public :
    FPTree(int minSup);
    FPTree(int minSup, int partialLabel, FPTree *parentProj);
    virtual ~FPTree();
    
    static void processFile(string fileName, int minSup);
    void createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void createTree(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    void insertTransaction(DLinkedList *transactionItems, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void insertTransaction(FPTreeItem **buffer, int size, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void printHeaderTable();
    
    string getLabelPrefix();
    int getBaseLevel();
    
    int getMinSup();
    HeaderTable* getHeaderTable();
};
#endif