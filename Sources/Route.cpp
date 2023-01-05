#include "../Headers/Route.h"
#include <math.h>
#include <limits>

Route::Route(int capacity){
    this->capacity = capacity;
}
Route::Route(vector<Customer> order, int capacity){
    this->order = order;
    this->capacity = capacity;
}

double Route::length() {
    double length = 0.0;
    for(int i = 0; i < order.size() - 2; i++){
        length += order[i].distance(order[i + 1]);
    }
    return length;
}

pair<double,int> Route::distanceFromRoute(Customer customer){
    
    double min_elongation = numeric_limits<double>::max();
    int insertion_point = 0;
    int n = order.size();
    for(int i = 0; i < n; i++){
        double elongation = customer.distance(order[i]) + customer.distance(order[(i+1) % n]) - order[i].distance(order[(i+1) % n])
                                - order[i].distance(order[(i + 1) % n]);
        if(elongation < min_elongation){
            min_elongation = elongation;
            insertion_point = i;
        }
    }  
    return {min_elongation,insertion_point + 1};

}

bool Route::checkConstraints(vector<Customer> route){

    double time = 0;
    for(int i = 1; i < route.size(); i++){
        time += route[i].distance(route[i-1]);
        if(route[i].getReadyTime() > time) time = route[i].getReadyTime();
        if(route[i].getDueDate() < time) return false;
        time += route[i].getServiceTime();
    }

    return true;
    
}

bool Route::addToRoute(Customer customer,int insertion_point){
    
    if(customer.getDemand() > capacity) return false;

    vector<Customer> route_copy(order);
    if(insertion_point == order.size()){
        route_copy.push_back(customer);
    } else {
            route_copy.insert(route_copy.begin() + insertion_point,customer);
    }

    if(checkConstraints(route_copy)){
        order = route_copy;
        return true;
    }
    return false;

}



