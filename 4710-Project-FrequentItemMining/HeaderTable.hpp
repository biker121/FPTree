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

#define MAX_DOMAIN_ITEMS 1000

using namespace std;

class DOrderedList;
class FPTreeItem;
class HeaderItem;

class HeaderTable {
    
private:
//    HeaderItem *freqItems[MAX_DOMAIN_ITEMS]; //--refactor - remove
    
    DOrderedList *headerItems;
    int numDomainItems;
    int minSup;
    
    static bool populateHash(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    static void incrementHashItem(FPTreeItem *item, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    static bool insertHeaderItems(HeaderTable *headerTable, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
public:
    HeaderTable(int minSup);
    virtual ~HeaderTable();
    
    bool createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void printTable();
    
    static int getHashIndex(FPTreeItem *item);
    
    //debug
//    void verifyFrequencies();
    
    //************* GETTERS ***************
    int getNumDomainItem();
};

#endif
