//
// Created by roy on 02/04/2016.
//

#include "FoldersMapReduceClient.h"
#include "MapReduceFramework.h"
#include <dirent.h>

//------------ FolderMapReduce implementation ---------------

/**
 * //TODO HANDLE IMPORTANT -- AS OF NOW IT'S THE FRAMEWORK'S RESPONSIBILITY TO FREE THE EMITTED <K2,V2>'S
 * @param key a pathName(FolderNameKey) to a directory.
 * @param val a substring(SubString) to look for in the file names in the folder.
 */
void FolderMapReduce::Map(const k1Base *const key, const v1Base *const val) const
{
    string dirPath = ((FolderNameKey *) key)->getPathName();
    string sStr = ((SubString *) val)->getSubStr();
    DIR *dp;
    dirent *fileEntry;
    dp = opendir(dirPath.c_str());
    if (dp == NULL)
    {
        //todo handle error
    }

    string fileName;
    size_t found;
    k2Base *key2;
    v2Base *val2;
    while (fileEntry = readdir(dp))
    {
        fileName = fileEntry->d_name;
        found = fileName.find(sStr);
        if (found != std::string::npos) //if substring exists
        {
            key2 = new FileNameKey(fileName);
            val2 = new StupidCount();
            Emit2(key2, val2);//todo free somewhere
        }
    }

    if (closedir(dp) == -1) //-1 is returned upon error
    {
        //todo handle error
    }
}

void FolderMapReduce::Reduce(const k2Base *const key, const V2_LIST &vals) const //typedef std::list<v2Base *> V2_LIST;
{
//    std::list<v2Base *>::iterator

    v3Base *val3 = new Counter(vals.size());//counts the number of 1's in the list
    k3Base *key3 = new ShittyFileNameKey(((FileNameKey *) key)->getFileName());
    Emit3(key3, val3);
}


//------------ FolderNameKey(k1Base) implementation ---------------
FolderNameKey::FolderNameKey(string pathName) : pathName(pathName) {}

/**
 * operator < implementation
 */
bool FolderNameKey::operator<(const k1Base &other) const
{
//    const FolderNameKey *othr = dynamic_cast<FolderNameKey *>(&other);
    const FolderNameKey *othr = (FolderNameKey *) &other; //Assumes other is an up-cast of FolderNamKey

    return (this->pathName < othr->pathName);
}

string FolderNameKey::getPathName()
{
    return pathName;
}

//------------ FolderSubStringNameKey(v1Base) implementation ---------------

SubString::SubString(string subStr) : subStr(subStr){}
string SubString::getSubStr()
{
    return subStr;
}

//------------ FileNameKey(k2Base) implementation ---------------

FileNameKey::FileNameKey(string fileName) : fileName(fileName) {}

bool FileNameKey::operator<(const k2Base &other) const
{
    const FileNameKey *othr = (FileNameKey *) &other;//Assumes other is an up-cast of FileNameKey. Maybe change to dynamic_cast
    return (this->fileName < othr->fileName);
}

string FileNameKey::getFileName()
{
    return fileName;
}

//------------ StupidCount(v2Base) implementation ---------------

//StupidCount::StupidCount(int count) : count(count) {}
int StupidCount::getCount()
{
    return count;
}

//------------ ShittyFileNameKey(k3Base) implementation ---------------

ShittyFileNameKey::ShittyFileNameKey(string fileName) : fileName(fileName) {}
bool ShittyFileNameKey::operator<(const k3Base &other) const
{
    const ShittyFileNameKey *othr = (ShittyFileNameKey *) &other;//Assumes other is an up-cast of ShittyFileNameKey. Maybe change to dynamic_cast
    return (this->fileName < othr->fileName);
}

string ShittyFileNameKey::getFileName()
{
    return fileName;
}
//------------ Counter(v3Base) implementation ---------------

Counter::Counter(unsigned long count) : count(count) {}
unsigned long Counter::getCount()
{
    return count;
}