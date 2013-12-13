//
//  Data.hpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 12/12/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#ifndef _710_Project_FrequentItemMining_Data_hpp
#define _710_Project_FrequentItemMining_Data_hpp

//-----------------------------------------------------------------------------------------
// CLASS: Data
//
// Author: Brahmdeep Singh Juneja
//
// REMARKS: Basic atomic data class
//-----------------------------------------------------------------------------------------
class Data {
public:
    virtual	~Data();
    virtual void print()                    = 0;
    virtual bool isEqualsTo(Data *other)    = 0;
};

#endif
