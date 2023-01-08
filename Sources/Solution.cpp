#include "../Headers/Solution.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <filesystem>


using namespace std;


Solution::Solution(int capacity){
    this->routes.clear();
    this->capacity = capacity;
}

bool Solution::CompareByReadyTime(Customer a, Customer b){
    return a.getReadyTime() < b.getReadyTime();
}

bool Solution::CompareById(Customer a, Customer b){
    return a.getId() < b.getId();
}


Solution::Solution(vector<Route> routes, int capacity){
    this->routes = routes;
    this->capacity = capacity;
}

double Solution::length(){
    double distance = 0.0;
    for(auto route : routes) distance += route.length();
    return distance;
}

int Solution::size() {
    return this->routes.size();
}

void Solution::addRoute(Route route){
    routes.push_back(route);
}


void Solution::print(string filename){
    cout << "Printing greedy solution\n";
    filesystem::path cwd = filesystem::current_path();
    string outfile = cwd.string() + '\\' + "out\\res-un-" + filename;
    ofstream file;
    file.open(outfile);
    printf("%d\n", routes.size());
    string output;
    output = to_string(routes.size()) + "\n";
    file<<output;
    
    for (int i = 0; i < routes.size(); i++){

        printf("%d: ", i + 1);
        output = to_string(i+1) + ": "; 
        double current_time = 0;

        vector<pair<Customer, int> > order_with_time = routes[i].order_with_time;
        
        for(int j = 0; j < order_with_time.size(); j++){
            printf("%d(%d)", order_with_time[j].first.getId(), order_with_time[j].second);
            output += to_string(order_with_time[j].first.getId()) +"(" + to_string(order_with_time[j].second) + ")";
            if(j != order_with_time.size() - 1){
                printf("->");
                output+="->";
            }
        }

        cout << '\n';
        output += "\n";
        file << output;
    }
    char buffer[100];
    sprintf(buffer,"%.2lf\n", length());
    printf("%.2lf\n", length());
    file<<buffer;
    file.close();
}
