#include <iostream>
using namespace std;

int main(){
    for(int i = 1; i <= 5; i++){
        string cmd = "main.exe i" + to_string(i) + ".csv";
        system(cmd.c_str());
    }
    return 0;
}