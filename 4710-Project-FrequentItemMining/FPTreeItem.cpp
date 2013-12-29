#include "HeaderTable.hpp"
#include "FPTreeItem.hpp"

//--------------------------------------------------------------------------//
//  FPTreeItem
//
//  <FPTree> data type containing domain item and it's support 
//--------------------------------------------------------------------------//

FPTreeItem::FPTreeItem()
{
    this->data = 0;
    this->support = 0;
}

FPTreeItem::FPTreeItem(int data, int support)
{
    this->data = data;
    this->support = support;
}

FPTreeItem::~FPTreeItem(){}

/**
 * PURPOSE: increases the frequency by one
 */
void FPTreeItem::increaseSupport()
{
    this->support++;
}

/**
 * PURPOSE: increases the frequency by a given value
 */
void FPTreeItem::increaseSupport(int inc)
{
    this->support+=inc;
}

/**
 * PURPOSE: increases frequency by the frequency of given item
 */
void FPTreeItem::increaseSupport(FPTreeItem *item)
{
    if (item != NULL)
        this->support += item->support;
}


/**
 * PURPOSE: compares based on frequency and returns an integer representing result of
 *          comparison
 * PARAM  : OrderedItem *, item that is to be compared
 * RETURN : 0 -> if both FPTreeItems have same data value and support
 *         +1 -> this TreeItem would appear after  the given, in alphabetical order
 *         -1 -> this TreeItem swould appear before the given, in alphabetical order
 */
int FPTreeItem::compareTo(OrderedData *item)
{
    FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(item);
    int result = 0;
    
    if (otherFPTreeItem != NULL)
    {
        result = this->support - otherFPTreeItem->support;
        
        if (result == 0) //compare canonical order
            result = otherFPTreeItem->data - this->data;
    }
    
    return result;
}

bool FPTreeItem::isEqualsTo(OrderedData *target)
{
    FPTreeItem *otherFPTreeItem = dynamic_cast<FPTreeItem *>(target);
    bool result = false;
    
    if (otherFPTreeItem != NULL && this->data == otherFPTreeItem->data)
        result = true;
    
    return result;
}

/**
 * PURPOSE: prints data item and frequency
 */
void FPTreeItem::print()
{
    cout << this->data << " : " << this->support;
}

//------- GETTERS ----------------------------------------------------//

int FPTreeItem::getData()
{
    return this->data;
}

int FPTreeItem::getSupport()
{
    return this->support;
}