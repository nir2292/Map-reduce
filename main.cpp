#include <iostream>
#include <vector>

#include "MapReduceClient.h"
#include "MapReduceFramework.h"
#include "FoldersMapReduceClient.h"

using namespace std;

typedef std::vector<FolderNameKey *> FoldersVector;

const string NO_ARGS_ERROR_MESSAGE = "Usage: <substring to search> <folders, separated by space>";

void printNoArgError();

/**
 * Produces an array of FolderNameKey instances from argv
 */
void getPathNames(int argc, char *argv[], FoldersVector &pathNames)
{
    for (int i=2; i <= argc; ++i)
    {
        pathNames[i-2] = new FolderNameKey(argv[i]);
    }
}

/**
 * Prints the results of the search
 */
void printOutList(OUT_ITEMS_LIST outs)
{
    ShittyFileNameKey *file;
    Counter *count;
    OUT_ITEMS_LIST::const_iterator it;
    for (it = outs.cbegin(); it != outs.cend(); ++it)
    {
        file = (ShittyFileNameKey *) it->first;
        count = (Counter *) it->second;
        for (int i=0; i < count->getCount(); ++i)
        {
            cout << file->getFileName() << " ";
        }
    }
}

void freeOutList(OUT_ITEMS_LIST outs) //todo check if this crap works
{
    OUT_ITEMS_LIST::iterator it;
    for (it = outs.begin(); it != outs.end(); ++it)
    {
        delete(it->first);
        delete(it->second);
    }
}

void freePathNames(FoldersVector pathNames)//todo also check if this crap works
{
    FoldersVector::iterator it;
    for (it=pathNames.begin(); it != pathNames.end(); ++it)
    {
        delete(*it);
    }
}

int main(int argc, char *argv[])
{
    FolderMapReduce mapReducer;


    if (argc == 1)
    {
        printNoArgError();//TODO write error func
    }
    else
    {
        string subStr = argv[1];
        FoldersVector pathNames;
        //FolderNameKey *pathNames[argc-2];
        v1Base *subString = new SubString(subStr);
        getPathNames(argc, argv, pathNames);

        IN_ITEMS_LIST inList;
        IN_ITEM inIt;


        for (int i=0; i < argc-2; ++i)
        {
            inIt = std::make_pair(pathNames[i], subString);
            inList.push_back(inIt);
        }

        OUT_ITEMS_LIST outs = runMapReduceFramework(mapReducer, inList, 1);

        //typedef std::pair<k3Base*, v3Base*> OUT_ITEM -- typedef std::list<OUT_ITEM> OUT_ITEMS_LIST;

        printOutList(outs);
        freeOutList(outs);
        freePathNames(pathNames);
    }

    return 0;
}



void printNoArgError()
{
    std::cerr << NO_ARGS_ERROR_MESSAGE<< std::endl;
}