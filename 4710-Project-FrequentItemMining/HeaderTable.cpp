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
        prioritizeFrequencies();
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
        
        //cycle through each transaction
        if (numTransactions > 0){
            do {
                dataFile >> currTransaction >> transactionSize;
                
                //increment appropriate count
                for (int i=0; i<transactionSize; i++){
                    dataFile >> buffer[i];
                    
                    temp = new FPTreeItem(buffer[i], 1); //temp is later freed
                    this->increment(temp);
                }
                
            } while (currTransaction < numTransactions);
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
    while (i<numDomainItems && i>=0){
        if (freqItems[i] != NULL && freqItems[i]->getData()->getFrequency() >= minSup){
            i++;
        } else if (freqItems[i] != NULL && freqItems[i]->getData()->getFrequency() < minSup){
            delete(freqItems[i]);
            
            if (i != (numDomainItems-1)){
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
 * @purpose: applies insertion sort to order HeaderTable items in decreasing frequency
 *------------------------------------------------------------------------------
 */
void HeaderTable::prioritizeFrequencies(){
    insertionSort(freqItems, numDomainItems);
}

//sorts the array with the specified len, in descending order
void HeaderTable::insertionSort(FPTreeNode *array[], int len){
    FPTreeNode *temp;
    int j;
    
    for (int i=1; i<len; i++){
        temp = array[i];
        for (j=i; j>0 &&
             ((temp->getData()->compareTo(array[j-1]->getData()) > 0) //frequency check
                    || ((temp->getData()->compareTo(array[j-1]->getData()) == 0)
                            && (temp->getData()->getData() - array[j-1]->getData()->getData() < 0)) ); j--){
            array[j] = array[j-1];
        }
        array[j] = temp;
    }
}

//prioritizes given array of items according to header table
void HeaderTable:: prioritizeItems(FPTreeItem *array[], int size){
    FPTreeItem *temp;
    int j;
    
    //DEBUG
    stringstream ss1;
    for (int i=0; i<size; i++)
        ss1 << array[i]->getData() << " ";
    cout << ss1.str() << endl;
    
    
    for (int i=1; i<size; i++){
        temp = array[i];
        for (j=i; j>0 && (temp->getFrequency() < array[j-1]->getFrequency()); j--){
            array[j] = array[j-1];
        }
        array[j] = temp;
    }
    
    
    //DEBUG
    stringstream ss2;
    for (int i=0; i<size; i++)
        ss2 << array[i]->getData() << " ";
    cout << ss2.str() << endl;
    
    cout << "\n";
}

/*-----------------------find (FPTreeItem *)-----------------------------------
 * @purpose: searches for an FPTreeItem similar to the one given using compareTo()
 * @parm   : FPTreeItem, search target
 * @return : FPTreeNode, reference to the Node containing the item
 *-----------------------------------------------------------------------------
 */
FPTreeNode* HeaderTable::find(FPTreeItem *item){
    FPTreeNode *result = NULL;
    
    for (int i=0; i<this->numDomainItems && result == NULL; i++){
        if (freqItems[i] != NULL
                && (freqItems[i]->getData()->getData() - item->getData()) == 0){
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
        freqItems[numDomainItems] = new FPTreeNode(item, NULL, NULL);
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
    FPTreeNode* found;
    
    if (item != NULL){
        found = find(item);
        
        if (found != NULL){
            found->getData()->increment();
            delete(item);
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
            freqItems[i]->getData()->print();
        }
    }
    cout << endl;
}