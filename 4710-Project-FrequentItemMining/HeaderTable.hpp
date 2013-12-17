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

#include "HeaderItem.hpp"
#include "HeaderTable.hpp"

#define MAX_DOMAIN_ITEMS 1000

using namespace std;

class FPTreeItem;
class FPTreeNode;
class OrderedList;

class HeaderTable {
    
private:
    HeaderItem *freqItems[MAX_DOMAIN_ITEMS]; //unique idx per item*
    int numDomainItems;
    int minSup;
    
    static bool populateHash(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    static void incrementHashItem(HeaderItem *hash[MAX_DOMAIN_ITEMS], FPTreeItem *item);
    
    static bool insertHeaderItems(HeaderTable *headerTable, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    bool populateFrequencies(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]); //--refactor - remove
    void prioritizeFrequencies();
    
    void insertionSort(HeaderItem *array[], int len);
    int assignPriorities(HeaderItem *array[], int len);
    void hashItems(HeaderItem *items[], int len);
    
    void increment(FPTreeItem *item);
    
public:
    HeaderTable(int minSup);
    virtual ~HeaderTable();
    
    bool createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void printTable();
    
    void prioritizeItems(FPTreeItem *items[], int size); //might not be needed
    
    static int getHashIndex(FPTreeItem *item);
    bool isFrequent(FPTreeItem *item); //-refactor - remove
    
    void linkNode(FPTreeNode *node);
    
    //debug
    void verifyFrequencies();
    
    //************* GETTERS ***************
    int getNumDomainItem();
};

#endif
