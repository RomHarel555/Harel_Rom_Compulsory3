#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class File {
public:
    File(const string& name, int sizeMB);
    void ChangeName(const string& newName);
    void PrintInfo() const;
    const string& GetName() const;
    int GetSizeMB() const;
    time_t GetDateCreated() const;

private:
    string name;
    int sizeMB;
    time_t dateCreated;
};

class Folder {
public:
    Folder(const string& name);
    void AddFile(const string& name, int sizeMB);
    bool AddFolder(const string& name);
    File* FindFile(const string& name);
    Folder* FindFolder(const string& name);
    bool Rename(const string& newName);
    void ListContents() const;
    File* FindLargestFile() const;

private:
    string name;
    vector<File> files;
    vector<Folder> folders;
};
