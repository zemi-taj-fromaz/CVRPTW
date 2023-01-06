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
            if(visit_time <= customers[i].getDueDate() && route_demand_size + customers[i].getDemand() <= capacity){
                route.order_with_time.push_back({customers[i], max(visit_time, customers[i].getReadyTime())});
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

    Greedy(customers, depot, capacity).print();

    return 0;

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
    vector<Route> seedRoutes;
    for(auto seed : seeds){
        Route r({depot,seed},capacity);
        seedRoutes.push_back(r);
    }


    #pragma endregion

    
    vector<Customer> L;
    sort(customers.begin(),customers.end(),Solution::CompareById);
    set_difference(customers.begin(),customers.end(),convexHull.begin(),convexHull.end(),
                        inserter(L,L.begin()));
    
    Solution solution(seedRoutes,capacity);
    solution.__greedy__(L,depot);

    solution.print();
  
    return 0;
}
