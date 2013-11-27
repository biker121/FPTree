//
//  HeaderTable.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderTable.hpp"

HeaderTable::HeaderTable(){
    this->numDomainItems = 0;
}

HeaderTable::~HeaderTable(){
    for (int i=0; i<numDomainItems; i++){
        delete(freqItems[i]);
    }
}

/*-----------------------createHeaderTable(string, int)-----------------------------------
 * @purpose: creates a header table based on the given data file, with only frequent items
 * @parm   : string fileName, absolute file name
 * @parm   : int minSup, support threshold for frequent items
 * @return : bool success, indicating whether or not table was created successfully
 *----------------------------------------------------------------------------------------
 */
bool HeaderTable::createHeaderTable(string fileName, int minSup){
    bool tableCreated = false;
    int numInfrequentItems = 0;
    
    tableCreated = populateFrequencies(fileName);
    if (tableCreated){
        numInfrequentItems = removeInfrequentItems(minSup);
        prioritize();
    }
    
    return tableCreated;
}


bool HeaderTable::populateFrequencies(string fileName){
    bool success = false;
    ifstream dataFile;    //the input file
    int numTransactions;
    int currTransaction, transactionSize;
    int buffer[MAX_DOMAIN_ITEMS];
    
    FPTreeItem *temp;
    
    dataFile.open(fileName.c_str());
    
    if ( dataFile.is_open() == false ){
        cout<<"Error while opening file. "<< endl;
    } else {
        dataFile >> numTransactions;
        dataFile >> currTransaction >> transactionSize;
        
        //cycle through each transaction
        while (currTransaction < numTransactions){
            
            //increment appropriate count
            for (int i=0; i<transactionSize; i++){
                dataFile >> buffer[i];
                
                temp = new FPTreeItem(buffer[i], 1, NULL);
                increment(temp);
            }
            
            dataFile >> currTransaction >> transactionSize;
        }
        
        dataFile.close();
        success = true;
    }
    return success;
}

int HeaderTable::removeInfrequentItems(int minSup){
    int count = 0;  //number of infrequent items found
    int i = 0;
    
    //cycle through each item while removing infrequent items
    while (i<numDomainItems){
        if (freqItems[i] != NULL && freqItems[i]->getCount() >= minSup){
            i++;
        } else if (freqItems[i] != NULL && freqItems[i]->getCount() < minSup){
            delete(freqItems[i]);
            
            if ( i != (numDomainItems-1)){
                freqItems[i] = freqItems[numDomainItems-1];
            }
            
            numDomainItems--;
            count++;
        }
    }
    
    cout << "# of infrequent 1-item sets removed - " << count << endl;
    
    return count;
}

/*-----------------------prioritize()-------------------------------------------
 * @purpose: applies insertion sort to order the items in decreasing frequency
 *------------------------------------------------------------------------------
 */
void HeaderTable::prioritize(){
    cout << endl;
    
    insertionSort(freqItems, numDomainItems);
}

//sorts the array with the specified len, in descending order
void HeaderTable::insertionSort(FPTreeItem *array[], int len){
    FPTreeItem *temp;
    int j;
    
    for (int i=1; i<len; i++){
        temp = array[i];
        for (j=i; j>0 && temp->compareFrequencyTo(array[j-1]) > 0; j--){
            array[j] = array[j-1];
        }
        array[j] = temp;
    }
}

/*-----------------------find (FPTreeItem *)-----------------------------------
 * @purpose: searches for the item similar to the given using compareTo()
 * @parm   : FPTreeItem, search target
 * @return : FPTreeItem, reference to the item found in the table
 *-----------------------------------------------------------------------------
 */
FPTreeItem* HeaderTable::find(FPTreeItem *item){
    FPTreeItem *result = NULL;
    
    for (int i=0; i<this->numDomainItems && result == NULL; i++){
        if (freqItems[i] != NULL && freqItems[i]->compareTo(item) == 0){
            result = freqItems[i];
        }
    }
    
    return result;
}

/*-----------------------add (FPTreeItem *)-----------------------------------
 * @purpose: adds the given item to the table
 * @parm   : FPTreeItem, item to be added
 *-----------------------------------------------------------------------------
 */
void HeaderTable::add(FPTreeItem *item){
    if ( (numDomainItems+1) < MAX_DOMAIN_ITEMS){
        freqItems[numDomainItems] = item;
        numDomainItems++;
    }
}

/*-----------------------increment (FPTreeItem *)-----------------------------------
 * @purpose: increments the count for the given item in the table
 *           - If the item does not exist, then adds the given item to table
 *           - else increments the existing similar item in table
 * @parm   : FPTreeItem, item to be incremented
 *-----------------------------------------------------------------------------
 */
void HeaderTable::increment(FPTreeItem *item){
    FPTreeItem* found;
    
    if (item != NULL){
        found = find(item);
        
        if (found != NULL){
            found->increment();
            delete item;
        } else {
            add(item);
        }
    }
}

/*-----------------------print()-------------------------------------------------
 * @purpose: simply prints the entire header table
 *------------------------------------------------------------------------------
 */
void HeaderTable::printTable(){
    cout << "Header table: " << endl;
    
    for (int i=0; i<numDomainItems; i++){
        if (freqItems[i] != NULL){
            freqItems[i]->print();
        }
    }
    cout << endl;
}