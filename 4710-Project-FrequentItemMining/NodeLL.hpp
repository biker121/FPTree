#ifndef _710_Project_FrequentItemMining_NodeLL_hpp
#define _710_Project_FrequentItemMining_NodeLL_hpp

class NodeLL;
class OrderedData;

class NodeLL
{
    
private:
    OrderedData *data;
    NodeLL *prev;
    NodeLL *next;
    
public:
    NodeLL(OrderedData *data, NodeLL *prev, NodeLL *next);
    NodeLL(OrderedData *data);
    virtual ~NodeLL();
    
    void print();
    
    //---------------------GETTERS--------------------------//
    
    OrderedData *getData();
    NodeLL *getPrev();
    NodeLL *getNext();
    
    //---------------------SETTERS--------------------------//
    
    void setData(OrderedData *data);
    void setPrev(NodeLL *prev);
    void setNext(NodeLL *next);
};


#endif
