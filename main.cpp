///CTRL+SHIFT+P for user snippets
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Sources/DataLoader.cpp"
#include "Sources/Customer.cpp"
#include "Sources/Solution.cpp"
#include "Sources/GiftWrapper.cpp"
#include "Sources/Greedy.cpp"

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

int main(int argc, char *argv[]){

    DataLoader* dataLoader = new DataLoader("i1[2].TXT");

    vector<string> vs(dataLoader->__load__());

    auto instace_characteristics = split(vs[0],",");
    int vehicle_number = stoi(instace_characteristics[0]);
    int customer_number = vs.size() - 2;
    int capacity = stoi(instace_characteristics[1]);

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
    Greedy(customers, depot).print();

    GiftWrapper* giftWrapper = new GiftWrapper();

    vector<Customer> convexHull = giftWrapper->wrap(customers);

    #pragma region SelectSeedPoints
        
    double distanceFromDepot = 0;

    vector<bool> selected(convexHull.size(),false);

    double max_distance = 0;
    double max_distance_ind = 0;
    for(int i = 0; i < convexHull.size(); i++){
        distanceFromDepot = convexHull[i].distance(depot);
        if(distanceFromDepot > max_distance){
            max_distance = distanceFromDepot;
            max_distance_ind = i;
        }
    }
    
    selected[max_distance_ind] = true;
    vector<Customer> seeds;
    seeds.push_back(convexHull[max_distance_ind]);
    
    int min_routes = (int)( ceil(total_demand/(double)capacity));
    min_routes--;

    while(min_routes){
        
        double distanceFromSeeds = 0;
        max_distance = 0;
        max_distance_ind = 0;
        for(int i = 0; i < convexHull.size(); i++){
            if(selected[i]) continue;
            for(auto seed : seeds){
                distanceFromSeeds += seed.distance(convexHull[i]);
            }
            if(distanceFromSeeds > max_distance){
                max_distance = distanceFromSeeds;
                max_distance_ind = i;
            }
        }
        seeds.push_back(convexHull[max_distance_ind]);
        min_routes--;

    }


    #pragma endregion

    
    vector<Customer> L;
    set_difference(customers.begin(),customers.end(),convexHull.begin(),convexHull.end(),
                        inserter(L,L.begin()));
  
    return 0;
}
