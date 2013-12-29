#include <vector>
#include <string>

#include "FPTree.hpp"
#include "FPTreeNode.hpp"
#include "FPTreeItem.hpp"
#include "HeaderTable.hpp"
#include "HeaderItem.hpp"
#include "DataMining.hpp"
#include "DLinkedList.hpp"
#include "TransPathItem.hpp"
#include "NodeLL.hpp"

DataMining::DataMining()
{
    memset(this->k_level_itemset_counts, 0, (sizeof(int) * MAX_DOMAIN_ITEMS) );
}

DataMining::~DataMining()
{
}

void DataMining::processFile(string fileName, int minSup, int showFPs, int showTime, int countFPs, int countNodes)
{
    DataMining *dataMining = new DataMining();
    clock_t start;
    double duration;
    
    if (showFPs == 1)
    {
        cout << "---------showFPs=" << showFPs << "-----------" << endl;
    }
    
    //----------START---------
    start = clock();
    
    FPTree* globalTree = dataMining->createTree(fileName, minSup); //read, create, and mine tree
    dataMining->FPGrowthMine(globalTree, showFPs, countFPs);
    
    //----------END-------
    duration = (clock() - start) / (double)  CLOCKS_PER_SEC;
    
    if (showFPs == 1)
    {
        cout << endl;
    }
    
    if (showTime == 1)
    {
        cout << "--------showTime=" << showTime << "----------" << endl;
        cout << "runtime = " << duration << endl << endl;
    }
    
    if (countFPs == 1)
    {
        cout << "--------countFPs=" << countFPs << "-----------" << endl;
        for (int i=0; i<MAX_DOMAIN_ITEMS && dataMining->k_level_itemset_counts[i] != 0; i++)
            cout << "|L" << i+1 << "| = " << dataMining->k_level_itemset_counts[i] << endl;
        cout << endl;
    }
    
    if (countNodes == 1)
    {
        cout << "------countNodes=" << countNodes << "----------"<< endl;
        cout << "total globalNodes = " << globalTree->totalTreeNodes() << endl;
        cout << endl;
    }
}

// private helper method for findFreqItems()
void DataMining::getPrefix(int i, string &str, string &result)
{
    int count = 0;
    size_t pos = 0;
    size_t newPos = 0;
    std::string token;
    while ((newPos = str.find(',', pos)) != std::string::npos && count < i)
    {
        token = str.substr(pos, newPos-pos);
        pos=newPos+1;
        if(count == 0)
            result += token;
        else
            result += "," + token;
        
        count++;
    }
}

// finds all the permutations of a given single path items
void DataMining::findFreqItems(int k, vector<string> *items, string label, int labelSize, int showFPs)
{
    vector<string> *fitems = new vector<string>;
    string formattedLabel;
    
    if (label != "")
        formattedLabel = label + ",";
    
    if(k==1)
    {
        for(int i=0; i<items->size(); i++)
        {
            string curri = items->at(i);
            
            // record - relative 1-itemset
            k_level_itemset_counts[labelSize+k-1]++;
            
            if (showFPs == 1)
                cout << "{" << formattedLabel << items->at(i) << "}" << endl;
            
            for (int j=i+1; j<items->size(); j++)
            {
                string currj = items->at(j);
                string joint = curri + "," + currj;
                fitems->push_back(joint);
            }
        }
        
    }else if(k>1)
    {
        for(int i=0; i<items->size(); i++)
        {
            string curri = items->at(i);
            string prefix;
            
            getPrefix(k-1, curri, prefix);
            
            int j = i+1;
            bool matches = true;
            while(matches && j<items->size())
            {
                string currj = items->at(j);
                string currjPrefix;
                getPrefix(k-1, currj, currjPrefix);
                
                if (prefix.compare(currjPrefix)==0)
                {
                    string joint = curri + "," + currj.substr(currjPrefix.length() + 1);
                    fitems->push_back(joint);
                } else
                {
                    matches = false;
                }
                
                j++;
            }
        }
    }
    
    // record - relative k-itemsets, where k>1
    for (int i=0; i<fitems->size(); i++)
    {
        k_level_itemset_counts[labelSize+k]++;
        
        if (showFPs == 1)
            cout << "{" << formattedLabel << fitems->at(i) << "}" << endl; 
    }
    
    
    if (fitems->size()>1)
    {
        findFreqItems(k+1, fitems, label, labelSize, showFPs);
    }
}

void DataMining::FPGrowthMine(FPTree* tree, int showFPs, int countFPs)
{
    HeaderTable *headerTable = NULL;
    NodeLL *currHeaderNode = NULL;
    HeaderItem *headerItem = NULL;
    FPTree *newProjTree = NULL;
    HeaderTable *projHeader = NULL;
    FPTreeNode *currSimilarNode = NULL;
    
    // record - relative 0-itemset
    if (tree->getBaseLevel() > 0 && tree->getLabelPrefix() != "")
    {
        k_level_itemset_counts[tree->getBaseLevel()-1]++;
        
        if (showFPs == 1)
            cout << "{" << tree->getLabelPrefix() << "}" << endl;
    }
    
    if(tree->isEmpty() == false && tree->isSinglePath())
    {
        vector<string> *singletons = tree->getSinglePath();
        findFreqItems(1, singletons, tree->getLabelPrefix(), tree->getBaseLevel(), showFPs);
    } else
    {
    	headerTable = tree->getHeaderTable();
        
        // Iterates through each header item in the header table starting from
        // the bottom to the top
        currHeaderNode = dynamic_cast<NodeLL*>(headerTable->getLowestFreqNode());
        while(currHeaderNode != NULL)
        {
            headerItem = (HeaderItem*)currHeaderNode->getData();
            DLinkedList *paths[headerItem->getSimilarNodeCount()];
            DLinkedList *path = NULL;
            
            newProjTree = new FPTree(tree->getMinSup(), headerItem->getData()->getData(), tree);
            projHeader = newProjTree->getHeaderTable();
            
            int currPathIndex = 0;
            
            // Iterates over nodes in the FP tree starting with a given header item
            // and generates a new list containing that path following the global
            // FP tree sorting order
            currSimilarNode = headerItem->getFirstSimilarTreeNode();
            while(currSimilarNode != NULL)
            {
                paths[currPathIndex] = new DLinkedList();
                path = paths[currPathIndex];
                
                int currNodeSupport = currSimilarNode->getData()->getSupport();
                
                // generates a path by chasing the parent pointers
                FPTreeNode *parent = currSimilarNode->getParent();
                while(parent->getData()!=NULL)
                {
                    FPTreeItem *dataItem = parent->getData();
                    FPTreeItem *item = new FPTreeItem(dataItem->getData(), currNodeSupport);
                    TransPathItem *pathItem = new TransPathItem(item, paths[currPathIndex]);
                    NodeLL* addedPathNode = paths[currPathIndex]->addToFront(pathItem);
                    
                    // add to header table
                    HeaderItem *hItem = projHeader->insertByFreqOrder(dataItem->getData(), currNodeSupport);
                    hItem->linkNextPath(addedPathNode);
                    
                    parent = parent->getParent();
                }// end - path generate loop
                
                currPathIndex++;
                
                currSimilarNode = currSimilarNode->getNextSimilarNode();
                
            } // end - all paths generation loop
            
            // this removes all the infrequent items from the header table
            // while also filtering out the infrequents from the paths
            projHeader->removeInfrequent();
            
            // insert all paths and DELETE them
            for (int i=0; i<headerItem->getSimilarNodeCount(); i++)
            {
                newProjTree->insertTransaction(paths[i]);
                
                // also DELETE existing path because that is no longer needed
                delete(paths[i]);
            }
            
            FPGrowthMine(newProjTree, showFPs, countFPs);
            
            // going backwards from lowest to highest order
            currHeaderNode = currHeaderNode->getPrev();
        }
    }
}

/**
 * PURPOSE : primary handler method for mining a given datafile with indicated minsup
 * PARM    : string fileName, absolute file name
 * PARM    : int minSup, support threshold for frequent items
 */
FPTree* DataMining::createTree(string fileName, int minSup)
{
    HeaderItem **hash =  new HeaderItem *[MAX_DOMAIN_ITEMS];
    FPTree *tree = new FPTree(minSup);
    
    // first pass - populate frequent items
    tree->createHeaderTable(fileName, hash); //will also fill hash[] with frequent 1-itemsets
    
    // second pass - tree creation of frequent items
    if (tree->getHeaderTable()->getNumDomainItem() > 0) {
        tree->createTree(fileName, hash);
        
        delete[] hash; //DEBUG - double check**
    }
    
    return tree;
}