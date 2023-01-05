#include "../Headers/DataLoader.h"



DataLoader::DataLoader(string filename){
    this->filename = filename;
}

vector<string> DataLoader::__load__(){
    vector<string> vs;

    string datapath = "instances/" + this->filename;

    std::ifstream file(datapath);
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
