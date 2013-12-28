//
//  main.cpp
//  4710-Project-FrequentItemMining
//
//  Created by Brahmdeep Singh Juneja on 11/21/2013.
//  Copyright (c) 2013 Brahmdeep Singh Juneja. All rights reserved.
//

#include <string>
#include <iostream>

#include "DataMining.hpp"

using namespace std;
//-----------------------------------------------------------
// AUTHOR(S)	  :	Brahmdeep Singh Juneja, Sukhpreet Lotey
// COURSE		  : Comp 4710 - Data Mining
// INSTRUCTOR	  : Carson K. Leung
//
// REMARKS        : This implementation of an FP-Tree algorithm to mine data
//                  from a given data set.
//
//-----------------------------------------------------------

// REMARK:  work for all options is done regardless of option chosen but only specified
//          information is displayed
int main(int argc, const char * argv[])
{    
    if (argc == 7)
    {
        string fileName = argv[1];
        int minSup = atoi(argv[2]);

        int showFPs = atoi(argv[3]);
        int showTime = atoi(argv[4]);
        int countFPs = atoi(argv[5]);
        int countNodes = atoi(argv[6]);
        
        //**** DEBUG only ****
        fileName = "/Users/brahmdeepjuneja/Desktop/SukhBranch/test_files/test1.txt";
        minSup = 1;
        
        cout << "===== FP-growth TDB=" << fileName
                    << " minsup=" << minSup
                    << " showFPs=" << showFPs
                    << " showTime=" << showTime
                    << " countFPs=" << countFPs
                    << " countNodes=" << countNodes
                    << " =====" << endl;
        
        DataMining::processFile(fileName, minSup, showFPs, showTime, countFPs, countNodes);
        
        cout << "===== FP-growth TDB=" << fileName
                    << " minsup=" << minSup
                    << " showFPs=" << showFPs
                    << " showTime=" << showTime
                    << " cntFPs=" << countFPs
                    << " cntNodes=" << countNodes
                    << ": Completed =====" << endl;
    } else
    {
        cout << "Invalid parameters "                                               << endl
                << "Usage: FPgrowth TDB minsup showFPs showTime cntFPs cntNodes"    << endl
                    << "minsup   INTEGER"                                           << endl
                    << "showFPs  0(No) or 1(Yes) to show all FPs with sup"          << endl
                    << "showTime 0(No) or 1(Yes) to show runtime"                   << endl
                    << "cntFPs   0(No) or 1(Yes) to count #FPs (k-itemsets for each k and total #FPs)" << endl
                    << "cntNodes 0(No) or 1(Yes) to count #nodes"                   << endl
                    << endl;
    }
    
    cout << endl << "End of processing." << endl;
    
    return EXIT_SUCCESS;
}
