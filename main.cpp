///CTRL+SHIFT+P for user snippets
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <filesystem>

#include "Sources/DataLoader.cpp"
#include "Sources/Customer.cpp"
#include "Sources/Solution.cpp"
#include "Sources/GiftWrapper.cpp"

using namespace std;

#define iterator vector<int>::iterator
#define ll long long

#pragma region Split

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
#pragma endregion

#pragma region Greedy

bool CompareByReadyTime(Customer a, Customer b){
    return a.getReadyTime() < b.getReadyTime();
 }

 bool CompareById(Customer a, Customer b){
    return a.getId() < b.getId();
 }

 Solution Greedy(vector<Customer> customers, Customer depot, int capacity){
    Solution solution = Solution(capacity);
    Route route = Route(capacity);

    sort(customers.begin(), customers.end(), CompareByReadyTime);

    int route_demand_size = 0;

    while(!customers.empty()){
        cout << customers.size();
        if(route.order_with_time.empty()) route.order_with_time.push_back({depot, 0});
       
        pair<Customer, int> last = route.order_with_time[route.order_with_time.size() - 1];
        bool added = false;
       
        for(int i = 0; i < customers.size(); i++){
            int visit_time = last.second + last.first.getServiceTime() + (int) ceil(last.first.distance(customers[i]));
            visit_time = max(visit_time,customers[i].getReadyTime());
            if(visit_time <= customers[i].getDueDate() && route_demand_size + customers[i].getDemand() <= capacity
                    && visit_time + customers[i].getServiceTime() + depot.distance(customers[i]) <= depot.getDueDate()){
                route.order_with_time.push_back({customers[i], visit_time});
                customers.erase(customers.begin() + i);
                added = true;
                route_demand_size += customers[i].getDemand();
                break;
            }
        }
        if(added) continue;
        solution.addRoute(route);
        route = Route(capacity);
        route_demand_size = 0;
    }
    return solution;
 }

#pragma endregion

int main(int argc, char *argv[]){

    DataLoader* dataLoader = new DataLoader("instance1.csv");

    vector<string> vs(dataLoader->__load__());

    //for(auto s : vs){ cout<<s<<" "; }cout<<endl;

    auto instace_characteristics = split(vs[0],",");
    int vehicle_number = stoi(instace_characteristics[0]);
    int customer_number = vs.size() - 2;
    int capacity = stoi(instace_characteristics[1]);

    cout << capacity << endl;

    auto depot_init = split(vs[1],",");
    Customer depot(stoi(depot_init[0]),{stoi(depot_init[1]),stoi(depot_init[2])},stoi(depot_init[3]),stoi(depot_init[4]),stoi(depot_init[5]),stoi(depot_init[6]));

    vector<Customer> customers;
    Customer* customer = nullptr;

    double total_demand = 0;

    for(int i = 2; i < vs.size(); i++){
        auto customer_init = split(vs[i],",");
        customer = new Customer(stoi(customer_init[0]),{stoi(customer_init[1]),stoi(customer_init[2])},stoi(customer_init[3]),stoi(customer_init[4]),stoi(customer_init[5]),stoi(customer_init[6]));
        total_demand += customer->getDemand();
        customers.push_back(*customer);
    }

    filesystem::path cwd = filesystem::current_path() / "coordinates.txt";
    ofstream file(cwd.string());
    if(file){
        string output;
        output = to_string(depot.getCoord().first) + " " + to_string(depot.getCoord().second) + "\n";
        file << output;
        for(int i = 0; i < customers.size(); i++){
            auto coord = customers[i].getCoord();
            output = to_string(coord.first) + " " + to_string(coord.second) + "\n";
            file<<output;
        }
    }
    file.close();

    Greedy(customers, depot, capacity).print();

    return 0;
}
