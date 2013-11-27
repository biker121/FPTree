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
#include "HeaderTable.hpp"

using namespace std;

class HeaderTable {
    
private:
    FPTreeItem *freqItems[MAX_DOMAIN_ITEMS];
    int numDomainItems;

    void increment(FPTreeItem *item);
    FPTreeItem* find(FPTreeItem *item);
    void add(FPTreeItem *item);

    bool populateFrequencies(string fileName);
    int removeInfrequentItems(int minSup);
    void prioritize();
public:
    HeaderTable();
    virtual ~HeaderTable();
    
    bool createHeaderTable(string fileName, int minSup);
    void printTable();
    
    static void insertionSort(FPTreeItem *array[], int len);
};

#endif
