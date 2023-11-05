#include "comp3 header.h"
#include <cstdlib>
#include <ctime>

using namespace std;

File::File(const string& name, int sizeMB)
    : name(name), sizeMB(sizeMB) {
    dateCreated = time(0);
}

void File::ChangeName(const string& newName) {
    name = newName;
}

void File::PrintInfo() const {
    tm timeinfo;
    localtime_s(&timeinfo, &dateCreated);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%c", &timeinfo);

    cout << "File Name: " << name << endl;
    cout << "File Size: " << sizeMB << " MB" << endl;
    cout << "Date Created: " << buffer << endl;
}

const string& File::GetName() const {
    return name;
}

int File::GetSizeMB() const {
    return sizeMB;
}

time_t File::GetDateCreated() const {
    return dateCreated;
}

Folder::Folder(const string& name)
    : name(name) {
}

void Folder::AddFile(const string& name, int sizeMB) {
    if (files.size() < 10) {
        files.push_back(File(name, sizeMB));
    }
    else {
        cout << "Maximum number of files reached." << endl;
    }
}

bool Folder::AddFolder(const string& name) {
    if (folders.size() < 5) {
        folders.push_back(Folder(name));
        return true;
    }
    else {
        cout << "Maximum number of folders reached." << endl;
        return false;
    }
}

File* Folder::FindFile(const string& name) {
    for (File& file : files) {
        if (file.GetName() == name) {
            return &file;
        }
    }
    return nullptr;
}

Folder* Folder::FindFolder(const string& name) {
    for (Folder& folder : folders) {
        if (folder.name == name) {
            return &folder;
        }
    }
    return nullptr;
}

bool Folder::Rename(const string& newName) {
    if (newName != name) {
        name = newName;
        return true;
    }
    else {
        cout << "New name is the same as the old name." << endl;
        return false;
    }
}

void Folder::ListContents() const {
    cout << "Folder: " << name << endl;
    cout << "Files:" << endl;
    for (const File& file : files) {
        file.PrintInfo();
    }
    cout << "Subfolders:" << endl;
    for (const Folder& folder : folders) {
        cout << folder.name << endl;
    }
}

File* Folder::FindLargestFile() const {
    if (files.empty()) {
        return nullptr;
    }

    File* largestFile = &const_cast<File&>(files[0]);
    for (File& file : const_cast<vector<File>&>(files)) {
        if (file.GetSizeMB() > largestFile->GetSizeMB()) {
            largestFile = &file;
        }
    }
    return largestFile;
}
