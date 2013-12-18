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

#include "FPContants.hpp"
#include "HeaderItemList.h"

using namespace std;

class FPTreeItem;
class HeaderItem;
class HeaderItemList;

class HeaderTable {
    
private:    
    HeaderItemList *headerItems;
    int numDomainItems;
    int minSup;
    
    static bool populateHash(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    static bool insertHeaderItems(HeaderTable *headerTable, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    static void incrementHashItem(FPTreeItem *item, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
public:
    HeaderTable(int minSup);
    virtual ~HeaderTable();
    
    HeaderItem* insertByFreqOrder(int domainItem);
    bool createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void printTable();
    
    static int getHashIndex(FPTreeItem *item);
    
    //debug
    //void verifyFrequencies();
    
    //************* GETTERS ***************
    int getNumDomainItem();
    NodeLL* getLowestFreqNode();
    NodeLL* getHighestFreqNode();
};

#endif