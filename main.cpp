///CTRL+SHIFT+P for user snippets
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <chrono>

#include "Sources/DataLoader.cpp"
#include "Sources/Customer.cpp"
#include "Sources/Solution.cpp"

using namespace std;

#define iterator vector<int>::iterator
#define ll long long

#pragma region Timer

chrono::high_resolution_clock::time_point start_time;

double allowed_time;

double get_elapsed_time() {
  // get current time
  auto current_time = chrono::high_resolution_clock::now();

  // get duration since start of program
  auto elapsed_time = current_time - start_time;

  // convert duration to seconds and return as double
  return chrono::duration<double>(elapsed_time).count();
}

#pragma endregion

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

 Solution Greedy(vector<Customer> customers, Customer depot, int capacity, bool should_sort = true){
    Solution solution = Solution(capacity);
    Route route = Route(capacity);

    if(should_sort) sort(customers.begin(), customers.end(), CompareByReadyTime);

    int route_demand_size = 0;

    while(!customers.empty()){
        if(route.order_with_time.empty()) route.order_with_time.push_back({depot, 0});
       
        pair<Customer, int> last = route.order_with_time[route.order_with_time.size() - 1];
        bool added = false;
       
        for(int i = 0; i < customers.size(); i++){
            int visit_time = last.second + last.first.getServiceTime() + (int) ceil(last.first.distance(customers[i]));
            visit_time = max(visit_time,customers[i].getReadyTime());
            if((visit_time <= customers[i].getDueDate()) && (route_demand_size + customers[i].getDemand() <= capacity)
                    && (visit_time + customers[i].getServiceTime() + depot.distance(customers[i]) <= depot.getDueDate())){
                route.order_with_time.push_back({customers[i], visit_time});
                
                added = true;
                route_demand_size += customers[i].getDemand();
                customers.erase(customers.begin() + i);
                //cout<<route_demand_size<<endl;
                break;
            }
        }
        if(added) continue;
        route.order_with_time.push_back({depot,last.second + last.first.getServiceTime() + (int) ceil(last.first.distance(depot))});
        solution.addRoute(route);
        route = Route(capacity);
        route_demand_size = 0;
    }
    pair<Customer, int> last = route.order_with_time[route.order_with_time.size() - 1];
    route.order_with_time.push_back({depot,last.second + last.first.getServiceTime() + (int) ceil(last.first.distance(depot))});
    solution.addRoute(route);
        
    return solution;
 }

#pragma endregion

#pragma region RandomStartGreedy

Solution RandomStartGreedy(vector<Customer> customers, Customer depot, int capacity){
    Solution ret = Greedy(customers, depot, capacity);
    int last_improving = 0;
    int iterations = 0;
    while(true){
        iterations++;
        if(get_elapsed_time() > allowed_time * 60 - 0.5 || ++last_improving > 25000) break;
        sort(customers.begin(), customers.end(), CompareByReadyTime);
        int a = rand() % customers.size();
        int b = rand() % customers.size();
        if(a != b){
            Customer temp = customers[a];
            customers[a] = customers[b];
            customers[b] = temp;
        }
        Solution generated = Greedy(customers, depot, capacity, false);
        if(generated.isBetter(ret)) {
            ret = generated;
            last_improving = 0;
        }
    }
    cout << iterations << endl;
    return ret;
}

#pragma endregion


int main(int argc, char *argv[]){

    start_time = std::chrono::high_resolution_clock::now();

    srand(time(nullptr));
    string filename = argv[1];
    string timelimit = argv[2];
    allowed_time = timelimit != "un" ? stod(timelimit) : 1e6;

    DataLoader* dataLoader = new DataLoader(filename);

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
    RandomStartGreedy(customers, depot, capacity).print(filename,timelimit);

    printf("Finished in %.5lf\n", get_elapsed_time()); 

    return 0;
}
