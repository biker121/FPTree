//
//  PathItem.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/16/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_PathItem_hpp
#define _710_Project_FrequentItemMining_PathItem_hpp

#include <cstdlib>
#include "Data.hpp"

using namespace std;

class FPTreeItem;
class NodeLL;

class PathItem : public Data {
private:
    FPTreeItem *data;
    NodeLL *nextSimilarPathNode;
    
public:
    PathItem(FPTreeItem *data);
    ~PathItem();

    //************** GETTERS ****************
    FPTreeItem* getData();
    NodeLL* getNextSimilarPathNode();
    
    //************** SETTERS ****************
    void setData(FPTreeItem *data);
    void setNextSimilarPathNode (NodeLL *nextSimilarPathNode);
};

#endif
