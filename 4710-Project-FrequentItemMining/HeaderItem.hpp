#ifndef _710_Project_FrequentItemMining_HeaderItem_hpp
#define _710_Project_FrequentItemMining_HeaderItem_hpp

#include "OrderedData.hpp"

using namespace std;

class FPTreeItem;
class FPTreeNode;
class NodeLL;

class HeaderItem : public OrderedData
{
private:
    FPTreeItem *data;
    FPTreeNode *firstSimilarTreeNode;
    NodeLL *firstPathNode;
    NodeLL *lastPathNode;
    
public:
    HeaderItem(FPTreeItem *data);
    virtual ~HeaderItem();
    void removeInfreqPathItems();
    
    void linkTreeNode(FPTreeNode *treeNode, HeaderItem *hash[]);
    void linkNextPath(NodeLL *path);
    
    void print();
    int compareTo(OrderedData *other);
    
    void increaseSupport();
    void increaseSupport(int inc);
    
    //----------------------GETTERS-------------------------//
    FPTreeItem* getData();
    FPTreeNode* getFirstSimilarTreeNode();
    NodeLL* getFirstPathNode();
    NodeLL* getLastPathNode();
    int getSimilarNodeCount();
    
    //----------------------SETTERS-------------------------//
    void setFirstSimilarTreeNode(FPTreeNode *firstSimilarTreeNode);
    void setFirstPathNode(NodeLL *firstPathNode);
    void setLastPathNode(NodeLL *lastPathNode);
};

#endif