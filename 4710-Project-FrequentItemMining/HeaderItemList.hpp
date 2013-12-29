#ifndef ___710_Project_FrequentItemMining__HeaderItemList__
#define ___710_Project_FrequentItemMining__HeaderItemList__

class HeaderItem;
class NodeLL;
class FPTreeItem;

class HeaderItemList
{
private:
    NodeLL* head;
    NodeLL* tail;
    NodeLL* extract(int item);
    void orderedInsert(NodeLL *item);
    
public:
    HeaderItemList();
    virtual ~HeaderItemList();
    
    HeaderItem* insertByFreqOrder(HeaderItem* item);
    void orderedInsert(HeaderItem *item);
    void removeInfrequent(int minsup);
    void print();
    
    //----------------------GETTERS------------------------//
    
    NodeLL* getHeadNode();
    NodeLL* getTailNode();
    HeaderItem* getItem(FPTreeItem *item);
    int getSize();
};
#endif
