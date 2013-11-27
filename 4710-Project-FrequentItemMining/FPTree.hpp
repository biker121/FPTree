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

#include "HeaderTable.hpp"
#include "FPTree.hpp"

using namespace std;

class FPTree {
private:
    
public :
    static void processFile(string fileName, int minSup);
};
#endif
