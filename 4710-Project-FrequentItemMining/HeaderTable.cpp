//
//  HeaderTable.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderItem.hpp"
#include "HeaderTable.hpp"

HeaderTable::HeaderTable(int minSup){
    this->numDomainItems = 0;
    this->minSup = minSup;
}

HeaderTable::~HeaderTable(){
    if (numDomainItems > 0){
        for (int i=0; i<MAX_DOMAIN_ITEMS; i++){
            if (freqItems[i] != NULL){
                delete(freqItems[i]);
                freqItems[i] = NULL;
            }
        }
    }
}

/*-----------------------createHeaderTable(string, int)-----------------------------------
 * @purpose: creates a header table based on the given data file, with only frequent items
 * @parm   : string fileName, absolute file name
 * @parm   : int minSup, support threshold for frequent items
 * @return : bool success, indicating whether or not table was created successfully
 *----------------------------------------------------------------------------------------
 */
bool HeaderTable::createHeaderTable(string fileName){
    bool tableCreated = false;
    
    tableCreated = populateFrequencies(fileName);
    if (tableCreated){
        this->printTable();
        this->prioritizeFrequencies();
    }
    
    return tableCreated;
}

// @purpos e : records the frequency of items in the specified file in a hashed array
bool HeaderTable::populateFrequencies(string fileName){
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
                    this->increment(tempItem);
                    
                }
                
            } while (currTransaction < numTransactions);
        }
        
        dataFile.close();
        success = true;
    }
    return success;
}

/*------------------------------------------------------------------------------
 * @purpose: While maintaining hash, this method prioritizes data items in 
 *           drecreasing frequency and removes infrequent items
 *------------------------------------------------------------------------------
 */
void HeaderTable::prioritizeFrequencies(){
    HeaderItem *temp;
    HeaderItem *tempArray[MAX_DOMAIN_ITEMS];
    
    this->insertionSort(freqItems, MAX_DOMAIN_ITEMS);
    this->numDomainItems = this->assignPriorities(freqItems, numDomainItems);
    
    if (numDomainItems > 0){
        
        //copy over items to tempArray
        for (int i=0; i<this->numDomainItems; i++){
            temp = freqItems[i];
            tempArray[i] = temp;
            freqItems[i] = NULL;
        }
        
        this->hashItems(tempArray, this->numDomainItems);
    }
}

//sorts the array (including NULLS) in drecreasing frequency
void HeaderTable::insertionSort(HeaderItem *array[], int len){
    HeaderItem *temp;
    int j;
    
    for (int i=1; i<len; i++){
        temp = array[i];

        if (temp != NULL){
            //swap temp if it is higher priority
            for (j=i; j>0 &&
                 ((array[j-1] == NULL) || (temp->compareTo(array[j-1]) > 0))
                 ; j--){
                array[j] = array[j-1];
            }
            array[j] = temp;
        }
    }
}

//assigns priority to items based on their position in the given array
int HeaderTable::assignPriorities(HeaderItem *array[], int len){
    int currPriority = len; //which is also 'this->numDomainItems'
    bool infrequent = false;
    int numFrequentItems = 0;
    
    for (int i=0; i<len; i++){
        if (array[i] != NULL){
            
            if (!infrequent &&
                    array[i]->getData()->getData()->getFrequency() < this->minSup){
                infrequent = true;
                numFrequentItems = i;
            }
            
            if (infrequent){
                delete(array[i]);
                array[i] = NULL;
            } else {
                array[i]->setPriority(currPriority);
                currPriority--;
            }
        }
    }
    
    return numFrequentItems;
}

// @purpose : hashes the given items into the frequencyItems array
void HeaderTable::hashItems(HeaderItem *items[], int len){
    for (int i=0; i<len; i++){
        if (items[i] != NULL){
            this->freqItems[this->getHashIndex(items[i]->getData()->getData())] = items[i];
        }
    }
}

// @purpose : returns the hash index of the given item
int HeaderTable::getHashIndex(FPTreeItem *item){
    int result = -1;
    
    if (item != NULL){
        result = (item->getData() % MAX_DOMAIN_ITEMS) - 1;
    }
    
    return result;
}

/*-----------------------increment (FPTreeItem *)-----------------------------------
 * @purpose: increments the count for the given item in the table
 *           - If the item does not exist, then adds the given item to table
 *           - else increments the existing similar item in table
 * @parm   : FPTreeItem, item to be incremented
 *-----------------------------------------------------------------------------
 */
void HeaderTable::increment(FPTreeItem *item){
    HeaderItem* found;
    int hashIndex;

    if (item != NULL){
        hashIndex = getHashIndex(item);
        
        if (hashIndex >=0 && hashIndex < MAX_DOMAIN_ITEMS){
            found = freqItems[hashIndex];
            
            if (found == NULL){ //if no entry
                FPTreeNode *tempFPTreeNode = new FPTreeNode(item, NULL, NULL);
                HeaderItem *tempHeader  = new HeaderItem(tempFPTreeNode);
                this->freqItems[hashIndex] = tempHeader;
                this->numDomainItems++;
            } else {
                found->getData()->getData()->increment();
                delete(item);
            }
        }
    }
}

/*-----------------------print()-------------------------------------------------
 * @purpose: simply prints the entire header table
 *------------------------------------------------------------------------------
 */
void HeaderTable::printTable(){
    cout << "Header table: " << endl;
    int count = 0;
    int pos = 0;
    
    while (pos >= 0 && pos < MAX_DOMAIN_ITEMS && count < this->numDomainItems){
        if (this->freqItems[pos] != NULL){
            this->freqItems[pos]->print();
            count++;
        }
        pos++;
    }
    
    cout << endl;
}