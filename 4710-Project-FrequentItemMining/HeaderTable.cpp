//
//  HeaderTable.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderTable.hpp"

#include "NodeLL.hpp"
#include "DOrderedList.hpp"

#include "FPTreeNode.hpp"
#include "HeaderItem.hpp"

//------------------------Constructors and destructors-----------------------
HeaderTable::HeaderTable(int minSup){
    this->headerItems = new DOrderedList();
    
    this->numDomainItems = 0;
    this->minSup = minSup;
}
HeaderTable::~HeaderTable(){
    delete(headerItems);
    this->headerItems = NULL;
}//--------------------------------------------------------------------------

/*-------------------------------------------------------------------------------------
 * PURPOSE: creates a header table based on the given data file, with only frequent items
 * PARM   : fileName, absolute file name
 * PARM   : minSup, support threshold for frequent items
 * RETURN : bool success, indicating whether or not table was created successfully
 *-----------------------------------------------------------------------------------*/
bool HeaderTable::createHeaderTable(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    bool tableCreated = false;
    bool hashFilled = false;
    
    hashFilled = HeaderTable::populateHash(fileName, hash);
    
    if (hashFilled){
        tableCreated = HeaderTable::insertHeaderItems(this, hash);
    }
    
    return tableCreated;
}

// PURPOSE : fills the given hash with their frequency in the file
bool HeaderTable::populateHash(string fileName, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    bool success = false;
    ifstream dataFile;    //the input file
    int numTransactions;
    int currTransaction, transactionSize;
    
    FPTreeItem *tempItem;
    int temp;
    
    dataFile.open(fileName.c_str());
    
    if ( dataFile.is_open() == false ){
        cout<<"Error while opening file. "<< endl;
    } else {
        dataFile >> numTransactions;
        
        //cycle through each transaction
        if (numTransactions > 0){
            do {
                dataFile >> currTransaction >> transactionSize;
                
                //increment appropriate count
                for (int i=0; i<transactionSize; i++){
                    dataFile >> temp;
                    
                    tempItem = new FPTreeItem(temp, 1); //temp is later freed
                    HeaderTable::incrementHashItem(tempItem, hash);
                }
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
        success = true;
    }
    return success;
}

// PURPOSE : inserts frequent items from hash into header table list and removes
//           removes all infrequent items in hash
bool HeaderTable::insertHeaderItems(HeaderTable *headerTable, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    bool success = false;
    
    if (headerTable != NULL && hash != NULL){
        for (int i=0; i<MAX_DOMAIN_ITEMS; i++){
            if (hash[i] != NULL){ //frequent
                if (hash[i]->getData()->getSupport() < headerTable->minSup){
                    delete(hash[i]);
                    hash[i] = NULL;
                } else {
                    headerTable->headerItems->insert(hash[i]); //insert by frequency
                    headerTable->numDomainItems++;
                }
            }
        }
        
        success = true;
    }
    
    return success;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: returns the hash index of the given item by applying hash expresssion
 * PARM   : *item - which is to be evaluated for a hash index
 * RETURN : int - representing the hash index
 * REMARKS: - each item must have its own unique hash index
 *-----------------------------------------------------------------------------------*/
int HeaderTable::getHashIndex(FPTreeItem *item){
    int result = -1;
    
    if (item != NULL && item->getData() >= 0 && item->getData() < MAX_DOMAIN_ITEMS){
        result = item->getData() - 1;
    }
    
    return result;
}

void  HeaderTable::incrementHashItem(FPTreeItem *item, HeaderItem *hash[MAX_DOMAIN_ITEMS]){
    HeaderItem *found;
    int hashIndex = -1;
    
    if (item != NULL && hash != NULL){
        hashIndex = HeaderTable::getHashIndex(item);
        
        if (hashIndex >= 0 && hashIndex < MAX_DOMAIN_ITEMS){
            found = hash[hashIndex];
            
            if (found == NULL){ //if no entry
                hash[hashIndex] = new HeaderItem(item);
            } else {
                found->getData()->increaseSupport(item);
                delete(item);
            }
        }
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: simply prints the entire header table to console
 *-----------------------------------------------------------------------------------*/
void HeaderTable::printTable(){
    cout << "Header table: " << endl;
    headerItems->print();    
    cout << endl;
}

//************************* GETTERS ************************
int HeaderTable::getNumDomainItem(){ return this->numDomainItems; }