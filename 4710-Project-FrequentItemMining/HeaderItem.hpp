//
//  HeaderItem.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/28/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_HeaderItem_hpp
#define _710_Project_FrequentItemMining_HeaderItem_hpp

#include <cstdlib>
#include <string>
#include "HeaderTable.hpp"
#include "OrderedData.hpp"

using namespace std;

class FPTreeItem;
class FPTreeNode;
class NodeLL;

class HeaderItem : public OrderedData {
private:
    FPTreeItem *data;
    FPTreeNode *firstSimilarTreeNode;
    NodeLL *firstPathNode;

public:
    HeaderItem(FPTreeItem *data);
    ~HeaderItem();
    
    void linkTreeNode(FPTreeNode *treeNode, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void linkPathNode(NodeLL *pathNode, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    
    int compareTo(OrderedData *other); //--refactor -
    void print();
    
    //************* GETTERS *************
    FPTreeItem* getData();
    FPTreeNode* getFirstSimilarTreeNode();
    NodeLL* getFirstPathNode();
    
    //************* SETTERS *************
    void setFirstSimilarTreeNode(FPTreeNode *firstSimilarTreeNode);
    void setFirstPathNode(NodeLL *firstPathNode);
};

#endif