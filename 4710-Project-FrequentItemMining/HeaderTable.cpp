//
//  HeaderTable.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include "HeaderItem.hpp"
#include "FPTreeNode.hpp"
#include "HeaderTable.hpp"

//------------------------Constructors and destructors-----------------------
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
}//--------------------------------------------------------------------------

/*-------------------------------------------------------------------------------------
 * PURPOSE: creates a header table based on the given data file, with only frequent items
 * PARM   : fileName, absolute file name
 * PARM   : minSup, support threshold for frequent items
 * RETURN : bool success, indicating whether or not table was created successfully
 *-----------------------------------------------------------------------------------*/
bool HeaderTable::createHeaderTable(string fileName){
    bool tableCreated = false;
    
    tableCreated = populateFrequencies(fileName);
    if (tableCreated){
        this->prioritizeFrequencies();
    }
    
    return tableCreated;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: records the frequency of items in the specified file in a hashed array
 * PARM   : fileName - absolute path to the file that is to be read for reading frequency
 * RETURN : bool - indicating whether or not file was read properly
 *-----------------------------------------------------------------------------------*/
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

/*-------------------------------------------------------------------------------------
 * PURPOSE: While maintaining hash, this method orders items in decreasing frequency 
 *          and removes infrequent items
 *-----------------------------------------------------------------------------------*/
void HeaderTable::prioritizeFrequencies(){
    HeaderItem *temp;
    HeaderItem *tempArray[MAX_DOMAIN_ITEMS];
    
    this->insertionSort(freqItems, MAX_DOMAIN_ITEMS); //sort headerItems in decreasing frequency
    this->numDomainItems = this->assignPriorities(freqItems, numDomainItems);
    
    if (numDomainItems > 0){
        
        //copy over items to tempArray while maintaining order
        for (int i=0; i<this->numDomainItems; i++){
            temp = freqItems[i];
            tempArray[i] = temp;
            freqItems[i] = NULL;
        }
        
        //hash items
        this->hashItems(tempArray, this->numDomainItems);
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: prioritizes given array of items according to header table
 * PARM   : array[] which contains unprioritized list of FPTreeItems
 * PARM   : size of array[]
 * REMARKS: -- used for prioritizing FPTreeItems before passing array to for tree 
 *          insertion
 *-----------------------------------------------------------------------------------*/
void HeaderTable:: prioritizeItems(FPTreeItem *array[], int size){
    FPTreeItem *temp;
    int tempIndex;
    int j;

    for (int i=0; i<size; i++){
        tempIndex = this->getHashIndex(array[i]);
        
        if (freqItems[tempIndex] == NULL){
            delete(array[i]);
            array[i] = NULL;
        } else {
            temp = array[i];

            for (j=i; j>0
                    && ((array[j-1] == NULL)
                        || ((freqItems[tempIndex]->getPriority()
                            - freqItems[this->getHashIndex(array[j-1])]->getPriority())) > 0)
                    ; j--){
                array[j] = array[j-1];
            }
            array[j] = temp;
        }
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: sorts the array (including NULLS) in drecreasing frequency
 * PARM   : array[] to be sorted
 * PARM   : len - size of array[]
 *-----------------------------------------------------------------------------------*/
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

/*-------------------------------------------------------------------------------------
 * PURPOSE: assigns priority to items based on their position in the given array
 * PARM   : array[] - holds the items in decreasing priority
 * PARM   : len - size of the array[]
 * RETURN : int - representing the number of frequent items
 * REMARKS: higher priority is recognized by a higher priority #
 *-----------------------------------------------------------------------------------*/
int HeaderTable::assignPriorities(HeaderItem *array[], int len){
    int currPriority = len; //which is also 'this->numDomainItems'
    bool infrequent = false;
    int numFrequentItems = this->numDomainItems;
    
    for (int i=0; i<len; i++){
        if (array[i] != NULL){
            
            if (!infrequent &&
                    array[i]->getNode()->getData()->getFrequency() < this->minSup){
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

/*-------------------------------------------------------------------------------------
 * PURPOSE: hashes the given items into the freqItems array
 * PARM   : items[] - which holds items that are to be hashed
 * PARM   : len - size of items[]
 *-----------------------------------------------------------------------------------*/
void HeaderTable::hashItems(HeaderItem *items[], int len){
    for (int i=0; i<len; i++){
        if (items[i] != NULL){
            this->freqItems[this->getHashIndex(items[i]->getNode()->getData())] = items[i];
        }
    }
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
        result = (item->getData() % MAX_DOMAIN_ITEMS) - 1;
    }
    
    return result;
}

// @purpose :
//
// @return  : True if it exists in hashed array (aka is frequent), else false
/*-------------------------------------------------------------------------------------
 * PURPOSE: checks to see if the given item is hashed into the array to determine
 *          if it is frequent
 * PARM   : *item - that is to be evaluated
 * RETURN : True - if frequent, else false
 *-----------------------------------------------------------------------------------*/
bool HeaderTable::isFrequent(FPTreeItem *item){
    bool isFrequent = false;
    
    if (item != NULL && freqItems[this->getHashIndex(item)] != NULL){
        isFrequent = true;
    }
    
    return isFrequent;
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: increments the count for the given item in the table
 *          - If the item does not exist, then adds the given item to table
 *          - else increments the existing similar item in table
 * PARM   : FPTreeItem, item to be incremented
 *-----------------------------------------------------------------------------------*/
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
                found->getNode()->getData()->increment();
                delete(item);
            }
        }
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: adds the link to the given node for the appropriate headerItem
 * PARM   : *node - that is to be linked to the header table
 * REMARKS: - this method links the node without question
 *-----------------------------------------------------------------------------------*/
void HeaderTable::linkNode(FPTreeNode *node){
    int hashIndex = 0;
    
    if (node != NULL && node->getData() != NULL){
        hashIndex = getHashIndex(node->getData());
        
        if (hashIndex != -1 && freqItems[hashIndex] != NULL){
            node->setNextSimilarNode(freqItems[hashIndex]->getNode()->getNextSimilarNode());
            freqItems[hashIndex]->getNode()->setNextSimilarNode(node);
        }            
    }
}

/*-------------------------------------------------------------------------------------
 * PURPOSE: simply prints the entire header table to console
 *-----------------------------------------------------------------------------------*/
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

/*-------------------------------------------------------------------------------------
 * PURPOSE: for each header item, verifies its frequency with the tree
 * REMARKS: - if any of the frequencies don't match, it prints an error to console
 *-----------------------------------------------------------------------------------*/
void HeaderTable::verifyFrequencies(){
    int count;
    FPTreeNode *curr;
    bool frequenciesValid = true;
    
    for (int i=0; i<MAX_DOMAIN_ITEMS; i++){
        if (freqItems[i] != NULL){
            count = 0; //running frequency count
            
            curr = freqItems[i]->getNode()->getNextSimilarNode();
            while (curr != NULL){
                count += curr->getData()->getFrequency(); //add frequency
                curr = curr->getNextSimilarNode();
            }
            
            //if counted frequency doesn't match stored frequency --> print some details
            if (count != freqItems[i]->getNode()->getData()->getFrequency()){
                frequenciesValid = false;
                cout << endl;
                freqItems[i]->print();
                cout << "added frequeny = " << count << endl;
            }
        }
    }
    
    if (!frequenciesValid){
        cout << "error in frequency count" << endl;
    }
}

//************************* GETTERS ************************
int HeaderTable::getNumDomainItem(){ return this->numDomainItems; }