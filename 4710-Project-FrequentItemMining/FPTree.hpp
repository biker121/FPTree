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

class FPTree {
private:
    HeaderTable *headerTable;
    FPTreeNode *root;
    int minSup;
    string fileName;

    void createTree();
    void insertTransaction(FPTreeItem *items[], int size);
    void fp_growth(HeaderTable* h_table);
    void printTree();
    
public :
    FPTree(int minSup, string fileName);
    virtual ~FPTree();
    
    static void processFile(string fileName, int minSup);
    
    int getMinSup();
    string getFileName();
};
#endif