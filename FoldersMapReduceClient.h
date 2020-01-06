/**
* Created by roy on 02/04/2016.
* This is a user side implementation of the MapReduceFramework API
* meant to be linked with it.
*/


#ifndef SEARCH_FOLDERNAMEKEY_H
#define SEARCH_FOLDERNAMEKEY_H

#include <string>
#include "MapReduceClient.h"
using namespace std;



class FolderNameKey : public k1Base
{
    string pathName;

public:
    FolderNameKey (string pathName);
    bool operator<(const k1Base &other) const;
    string getPathName();
};

class SubString : public v1Base
{
    string subStr;
public:
    SubString(string subStr);
    string getSubStr();
};

class FileNameKey : public k2Base
{
    string fileName;
public:
    FileNameKey(string fileName);
    bool operator<(const k2Base &other) const;
    string getFileName();
};

class StupidCount : public v2Base
{
    const int count = 1;
public:
    //StupidCount(int count);
    int getCount();
};

class ShittyFileNameKey : public k3Base
{
    string fileName;
public:
    ShittyFileNameKey(string fileName);
    bool operator<(const k3Base &other) const;
    string getFileName();
};

class Counter : public v3Base
{
    unsigned long count;
public:
    Counter(unsigned long count);
    unsigned long getCount();
};

class FolderMapReduce : public MapReduceBase
{
public:
    void Map(const k1Base *const key, const v1Base *const val) const;
    void Reduce(const k2Base *const key, const V2_LIST &vals) const;
};


#endif //SEARCH_FOLDERNAMEKEY_H
