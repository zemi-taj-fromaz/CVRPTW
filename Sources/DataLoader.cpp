#include "../Headers/DataLoader.h"
#include <fstream>
#include <filesystem>

DataLoader::DataLoader(string filename){
    this->filename = filename;
}

vector<string> DataLoader::__load__(){
    vector<string> vs;

    
    filesystem::path cwd = filesystem::current_path() / ("instances/" + this->filename);

    ifstream file(cwd.string());
    if(file){
        string input;

        getline(file,input);
        getline(file,input);
        
        getline(file,input);
        vs.push_back(input);
        
        for (size_t i = 0; i < 4; i++)
        {
            getline(file,input);
        }

        while(getline(file,input)){
            vs.push_back(input);
        }
    }
    return vs;
}