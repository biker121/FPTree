//
//  OrderedData.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_OrderedData_hpp
#define _710_Project_FrequentItemMining_OrderedData_hpp

#include "Data.hpp"

using namespace std;
//-----------------------------------------------------------------------------------------
// CLASS: OrderedData
//
// Author: Brahmdeep Singh Juneja
//
// REMARKS: abstract class created to group objects together, in an ordered fashion
//-----------------------------------------------------------------------------------------
class OrderedData : public Data {
public:
    virtual int compareTo(OrderedData *)    = 0;
    virtual bool isEqualsTo(Data *other);
};

#endif
