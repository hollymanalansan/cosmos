#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#else
#include <dirent.h>
#endif

// Function to get files in directory
vector<string> GetFilesInDirectory(const string& directory) {
    vector<string> files;
#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directory + "\\*").c_str(), &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(directory + "\\" + findFileData.cFileName);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
#else
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_type == DT_REG) {
                files.push_back(directory + "/" + ent->d_name);
            }
        }
        closedir(dir);
    }
#endif
    return files;
}

int main() {
    // Extracting nfbs dataset
    system("tar -xf /content/NFBS_Dataset.tar.gz -C /content/");
    
    // Check the contents of each folder
    FILE* pipe = popen("ls /content/NFBS_Dataset/A00028185", "r");
    if (!pipe) {
        cerr << "Error: Unable to execute command\n";
        return 1;
    }
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            cout << buffer;
    }
    pclose(pipe);
    
    // Processing files
    vector<string> brain_mask;
    vector<string> brain;
    vector<string> raw;
    string root_dir = "/content/NFBS_Dataset";
    vector<string> files = GetFilesInDirectory(root_dir);
    
    // Iterate through files using iterators
    vector<string>::iterator it;
    for (it = files.begin(); it != files.end(); ++it) {
        const string& file = *it;
        if (file.find(".gz") != string::npos) {
            if (file.find("_brainmask.") != string::npos)
                brain_mask.push_back(file);
            else if (file.find("_brain.") != string::npos)
                brain.push_back(file);
            else
                raw.push_back(file);
        }
    }
    
    // Print the data
    cout << "Brain Masks:\n";
    for (it = brain_mask.begin(); it != brain_mask.end(); ++it)
        cout << *it << endl;
    cout << "\nBrains:\n";
    for (it = brain.begin(); it != brain.end(); ++it)
        cout << *it << endl;
    cout << "\nRaw Data:\n";
    for (it = raw.begin(); it != raw.end(); ++it)
        cout << *it << endl;

    return 0;
}


