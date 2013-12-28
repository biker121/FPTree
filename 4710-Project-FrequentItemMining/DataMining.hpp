//
//  DataMining.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DataMining_hpp
#define _710_Project_FrequentItemMining_DataMining_hpp

#include <string>
#include <vector>
#include "FPContants.hpp"

using namespace std;

class FPTree;

class DataMining {
    
private:
    DataMining();
    ~DataMining();
    
    int k_level_itemset_counts[MAX_DOMAIN_ITEMS];
    
    FPTree* createTree(string fileName, int minSup);
    void FPGrowthMine(FPTree* tree, int showFPs, int countFPs);
    void findFreqItems(int k, vector<string> *items, string label, int labelSize, int showFPs);
    void getPrefix(int i, string &str, string &result);
    
public:
    static void processFile(string fileName, int minSup, int showFPs, int showTime, int countFPs, int countNodes);
};

#endif
