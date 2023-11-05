#include "comp3 header.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void displayMenu() {
    cout << "===== Archive System Menu =====" << endl;
    cout << "1. Rename File or Folder" << endl;
    cout << "2. View File/Folder Info" << endl;
    cout << "3. List Files and Folders" << endl;
    cout << "4. Find Largest File in Folder" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Folder rootFolder("Root");

    // Create three folders, each containing five files with random sizes
    for (int i = 0; i < 3; ++i) {
        string folderName = "Folder" + to_string(i);
        Folder* newFolder = rootFolder.FindFolder(folderName);
        if (newFolder == nullptr) {
            rootFolder.AddFolder(folderName);
            newFolder = rootFolder.FindFolder(folderName);
        }
        for (int j = 0; j < 5; ++j) {
            string fileName = "File" + to_string(j);
            int fileSize = rand() % 101; // Random size between 0 and 100 MB
            newFolder->AddFile(fileName, fileSize);
        }
    }

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Rename File or Folder
            string nameToFind;
            cout << "Enter the name of the file or folder to rename: ";
            cin >> nameToFind;

            File* foundFile = rootFolder.FindFile(nameToFind);
            if (foundFile != nullptr) {
                string newName;
                cout << "Enter the new name: ";
                cin >> newName;
                foundFile->ChangeName(newName);
            }
            else {
                Folder* foundFolder = rootFolder.FindFolder(nameToFind);
                if (foundFolder != nullptr) {
                    string newName;
                    cout << "Enter the new name: ";
                    cin >> newName;
                    foundFolder->Rename(newName);
                }
                else {
                    cout << "File or folder not found." << endl;
                }
            }
        }
        else if (choice == 2) {
            // View File/Folder Info
            string infoName;
            cout << "Enter the name of the file or folder to view info: ";
            cin >> infoName;

            File* infoFile = rootFolder.FindFile(infoName);
            if (infoFile != nullptr) {
                infoFile->PrintInfo();
            }
            else {
                Folder* infoFolder = rootFolder.FindFolder(infoName);
                if (infoFolder != nullptr) {
                    infoFolder->ListContents();
                }
                else {
                    cout << "File or folder not found." << endl;
                }
            }
        }
        else if (choice == 3) {
            // List Files and Folders
            rootFolder.ListContents();
        }
        else if (choice == 4) {
            // Find Largest File in Folder
            string folderName;
            cout << "Enter the name of the folder to find the largest file: ";
            cin >> folderName;

            Folder* targetFolder = rootFolder.FindFolder(folderName);
            if (targetFolder != nullptr) {
                File* largestFile = targetFolder->FindLargestFile();
                if (largestFile != nullptr) {
                    cout << "Largest File in Folder " << folderName << ": " << largestFile->GetName() << endl;
                    largestFile->PrintInfo();
                }
                else {
                    cout << "No files found in the folder." << endl;
                }
            }
            else {
                cout << "Folder not found." << endl;
            }
        }
        else if (choice == 5) {
            // Exit the program
            return 0;
        }
        else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}
