#ifndef _710_Project_FrequentItemMining_FPTreeNode_hpp
#define _710_Project_FrequentItemMining_FPTreeNode_hpp

#include <cstdlib>
#include <string>
#include <sstream>

#include "FPContants.hpp"
#include "OrderedData.hpp"

using namespace std;

class NodeLL;
class FPTreeNode;
class DLinkedList;
class HeaderItem;
class FPTreeItem;
class HeaderTable;

class FPTreeNode : public OrderedData
{
private:
    FPTreeItem *data;
    FPTreeNode *nextSimilarNode;
    FPTreeNode *parent;
    FPTreeNode *nextSibling;
    FPTreeNode *headChild;
    
    void insertTransactionItem(FPTreeItem *items[MAX_DOMAIN_ITEMS], int size, int pos, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void insertTransactionItem(NodeLL *curr, HeaderTable *htable);
    
    FPTreeNode *insertChild(FPTreeItem *target, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    FPTreeNode *insertChild(FPTreeItem *target, HeaderTable *headerTable);
    
public:
    FPTreeNode();
    FPTreeNode(FPTreeItem *data, FPTreeNode *parent, FPTreeNode *nextSibling);
    virtual ~FPTreeNode();
    
    void insertTransaction(FPTreeItem *items[MAX_DOMAIN_ITEMS], int size, HeaderItem *hash[MAX_DOMAIN_ITEMS]);
    void insertTransaction(DLinkedList *items, HeaderTable *htable);
    
    //--------------------MINOR METHODS----------------------------//
    int compareTo(OrderedData *);
    bool isEqualsTo(OrderedData *);
    
    void print(int level);
    void print();
    
    bool hasSingleChild();
    int countNodes();
    
    //--------------------GETTERS---------------------------------//
    FPTreeItem* getData();
    FPTreeNode* getNextSimilarNode();
    FPTreeNode* getParent();
    FPTreeNode* getNextSibling();
    FPTreeNode* getHeadChild();
    
    //--------------------SETTERS---------------------------------//
    void setNextSibling(FPTreeNode *nextSibling);
    void setNextSimilarNode(FPTreeNode *nextSimilarNode);
};

#endif
