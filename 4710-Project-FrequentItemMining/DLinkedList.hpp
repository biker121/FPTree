#ifndef _710_Project_FrequentItemMining_DLinkedList_hpp
#define _710_Project_FrequentItemMining_DLinkedList_hpp

class NodeLL;
class OrderedData;

class DLinkedList
{
  
private:
    NodeLL *head;
    NodeLL *tail;
    int size;
    
public:
    DLinkedList();
    virtual ~DLinkedList();
    
    NodeLL *find(OrderedData *target);
    NodeLL *addToFront(OrderedData *item);
    NodeLL *addToBack(OrderedData *item);
    OrderedData* remove(OrderedData *target);
    
    void remove(NodeLL *node);
    void destory(OrderedData *target);
    void print();
    
    int getSize();
    NodeLL* getHead();
};

#endif
