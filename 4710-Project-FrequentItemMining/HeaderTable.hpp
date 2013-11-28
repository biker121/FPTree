//
//  HeaderTable.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_HeaderTable_hpp
#define _710_Project_FrequentItemMining_HeaderTable_hpp

#include <iostream>
#include <fstream>
#include <string>

#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"
#include "HeaderTable.hpp"

#define MAX_DOMAIN_ITEMS 1000

using namespace std;

class HeaderTable {
    
private:
    FPTreeNode *freqItems[MAX_DOMAIN_ITEMS];
    int numDomainItems;

    void increment(FPTreeItem *item);
    FPTreeNode* find(FPTreeItem *item);
    void add(FPTreeItem *item);

    bool populateFrequencies(string fileName);
    int removeInfrequentItems(int minSup);
    void prioritizeFrequencies();
public:
    HeaderTable();
    virtual ~HeaderTable();
    
    bool createHeaderTable(string fileName, int minSup);
    void printTable();
    
    static void insertionSort(FPTreeNode *array[], int len);
    static void prioritizeItems(FPTreeItem *array[], int size);
};

#endif
