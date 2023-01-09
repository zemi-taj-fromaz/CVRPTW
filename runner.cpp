#include <iostream>
using namespace std;
int main(int argc, char *argv[]){
    string time_limit = argv[1];
    for(int i = 1; i <= 5; i++){
        string cmd = "main.exe i" + to_string(i) + ".csv " + time_limit;
        system(cmd.c_str());
    }
    return 0;
}
