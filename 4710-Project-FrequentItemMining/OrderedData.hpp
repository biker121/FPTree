#ifndef _710_Project_FrequentItemMining_OrderedData_hpp
#define _710_Project_FrequentItemMining_OrderedData_hpp

#include <string>
#include <iostream>

using namespace std;

//--------------------------------------------------------------------------//
// OrderedData
//
// abstract class created to group objects together, in an ordered fashion
//--------------------------------------------------------------------------//

class OrderedData
{
    
public:
    virtual ~OrderedData();
    virtual int compareTo(OrderedData *other) = 0;
    virtual void print() = 0;
};

#endif
