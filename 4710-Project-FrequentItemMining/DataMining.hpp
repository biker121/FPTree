//
//  DataMining.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_DataMining_hpp
#define _710_Project_FrequentItemMining_DataMining_hpp

#include  <string>

class FPTree;

class DataMining {
public:
    static void FPGrowthMine(FPTree* tree, int base);
    static FPTree* processFile(string fileName, int minsup);
};

#endif
