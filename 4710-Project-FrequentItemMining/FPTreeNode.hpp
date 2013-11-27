//
//  FPTreeNode.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/27/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTreeNode_hpp
#define _710_Project_FrequentItemMining_FPTreeNode_hpp

#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"

using namespace std;

class FPTreeNode;

class FPTreeNode {    
private:
    FPTreeItem data;
    
    FPTreeNode *parent;
    void *headChild;

public:

    
};

#endif
