/** 
 *  ==============================================================================
 * 
 *          \file   test.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-27 18:38:05.216802
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public 
#include <iostream>
#include "common_util.h"
using namespace std;


void run()
{
		char sep = ' ';
		Pval(STRING(sep));
		Pval(std::to_string(sep));
		Pval(boost::lexical_cast<std::string>(sep));
    cout << "hahaha" << endl;
}

int main(int argc, char *argv[])
{
    run();

   return 0;
}
