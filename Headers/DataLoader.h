#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class DataLoader {
    private:
        string filename;
    public:
        DataLoader(string filename);
        vector<string> __load__();
};

#endif