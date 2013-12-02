//
//  FPTreeNode.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/27/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTreeNode_hpp
#define _710_Project_FrequentItemMining_FPTreeNode_hpp

#include <string>
#include <sstream>

#include "OrderedData.hpp"
#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"

using namespace std;

class FPTreeNode;

class FPTreeNode : public OrderedData {
private:
    FPTreeItem *data;
    FPTreeNode *nextSimilarNode;
    FPTreeNode *parent;
    FPTreeNode *nextSibling;
    FPTreeNode *headChild;
    
    FPTreeNode *incrementChild(FPTreeItem *target, HeaderTable *headerTable);
    
public:
    FPTreeNode();
    FPTreeNode(FPTreeItem *data, FPTreeNode *parent, FPTreeNode *nextSibling);
    virtual ~FPTreeNode();    
    
    void insertTransaction(FPTreeItem *items[], int size, int curr, HeaderTable *headerTable);
    
    //************* minor methods **********
    int compareTo(OrderedData *);
    void print();
    void print(int level);
    
    //************* GETTERS ****************
    FPTreeItem* getData();
    FPTreeNode* getNextSimilarNode();
    FPTreeNode* getParent();
    FPTreeNode* getNextSibling();
    FPTreeNode* getHeadChild();
    
    //************* SETTERS ****************
    void setNextSibling(FPTreeNode *nextSibling);
    void setNextSimilarNode(FPTreeNode *nextSimilarNode);
};

#endif
