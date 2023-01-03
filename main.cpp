///CTRL+SHIFT+P for user snippets
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Sources/DataLoader.cpp"
#include "Sources/Customer.cpp"
#include "Sources/Solution.cpp"

using namespace std;

#define iterator vector<int>::iterator
#define ll long long

vector<string> split(string str, string token){
    vector<string> result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

#pragma region Greedy

bool CompareByReadyTime(Customer* a, Customer* b){
    return a->getReadyTime() < b->getReadyTime();
}

Solution Greedy(vector<Customer*>& customers){
    sort(customers.begin(), customers.end(), CompareByReadyTime);
    Solution solution = Solution();
    //TODO write a solution that goes through orders by getReadyTimes
    //It is also possible to find a solution taking the elements by FinishedTime
        //where FinishedTime is defined as getReadyTime() + ServiceTime()
    return solution;
}

#pragma endregion

int main(int argc, char *argv[]){

    DataLoader* dataLoader = new DataLoader("i1[2].TXT");

    vector<string> vs(dataLoader->__load__());

    auto instace_characteristics = split(vs[0],",");
    int vehicle_number = stoi(instace_characteristics[0]);
    int customer_number = vs.size() - 2;
    int capacity = stoi(instace_characteristics[1]);

    auto depot_init = split(vs[1],",");
    Customer* depot = new Customer(stoi(depot_init[0]),{stoi(depot_init[1]),stoi(depot_init[2])},stoi(depot_init[3]),stoi(depot_init[4]),stoi(depot_init[5]),stoi(depot_init[6]));

    vector<Customer*> customers;
    Customer* customer = nullptr;
    for(int i = 2; i < vs.size(); i++){
        auto customer_init = split(vs[i],",");
        customer = new Customer(stoi(customer_init[0]),{stoi(customer_init[1]),stoi(customer_init[2])},stoi(customer_init[3]),stoi(customer_init[4]),stoi(customer_init[5]),stoi(customer_init[6]));
        customers.push_back(customer);
    }

  
    return 0;
}
