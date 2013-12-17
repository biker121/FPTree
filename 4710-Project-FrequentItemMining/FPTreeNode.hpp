//
//  FPTreeNode.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/27/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_FPTreeNode_hpp
#define _710_Project_FrequentItemMining_FPTreeNode_hpp

#include <cstdlib>
#include <string>
#include <sstream>

#include "OrderedData.hpp"
#include "DOrderedList.hpp"
#include "FPTreeItem.hpp"
#include "FPTreeNode.hpp"
#include "HeaderTable.hpp"

using namespace std;

class FPTreeNode;
class HeaderItem;

class FPTreeNode : public OrderedData {
private:
    FPTreeItem *data;
    FPTreeNode *nextSimilarNode;
    FPTreeNode *parent;
    FPTreeNode *nextSibling;
    FPTreeNode *headChild;
    
//    void insertTransactionItem(NodeLL *currTranscationItem, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void insertTransactionItem(FPTreeItem *items[MAX_DOMAIN_ITEMS], int size, int pos, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    FPTreeNode *insertChild(FPTreeItem *target, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
public:
    FPTreeNode();
    FPTreeNode(FPTreeItem *data, FPTreeNode *parent, FPTreeNode *nextSibling);
    virtual ~FPTreeNode();    
    
//    void insertTransaction(DOrderedList *items, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void insertTransaction(FPTreeItem *items[MAX_DOMAIN_ITEMS], int size, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    //************* minor methods **********
    int compareTo(OrderedData *);
    bool isEqualsTo(OrderedData *);
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
