#ifndef DATA_LOADER_H
#define DATA_LOADER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataLoader {
    private:
        string filename;
    public:
        DataLoader(string filename);
        vector<string> __load__();
};

#endif