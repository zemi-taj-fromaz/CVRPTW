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
    for(int i = 0; i < order_with_time.size() - 1; i++){
        length += order_with_time[i].first.distance(order_with_time[i + 1].first);
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

bool Route::checkConstraints(){
    double time = 0;
    double order_size;
    for(int i = 1; i < order.size(); i++){
        time += order[i].distance(order[i-1]);
        if(order[i].getReadyTime() > time) time = order[i].getReadyTime();
        if(order[i].getDueDate() < time) return false;
        time += order[i].getServiceTime();
        order_size += order[i].getDemand();
    }

    return order_size <= capacity;
}

bool Route::addToRoute(Customer customer, int insertion_point){
    
    if(customer.getDemand() > capacity) return false;

    order.insert(order.begin() + insertion_point, customer);

    //for(auto it : order) cout << it.getId() << ' ';
    //cout << (checkConstraints() ? "ok\n" : "not ok\n");

    if(checkConstraints()) return true;

    order.erase(order.begin() + insertion_point);
    return false;
}

void Route::removeRoute(int index){
    order.erase(order.begin() + index);
}

void Route::orderFromOWT(){
    order.clear();
    for(auto x : order_with_time) order.push_back(x.first);
}

void Route::OWTFromOrder(){
    order_with_time.clear();
    double time = 0;
    for(int i = 0; i < order.size(); i++){
        if(i != 0) time += order_with_time[i].first.distance(order_with_time[i-1].first);
        if(order_with_time[i].first.getReadyTime() > time) time = order_with_time[i].first.getReadyTime();
        time += order_with_time[i].first.getServiceTime();
        order_with_time.push_back({order[i], time});
    }
}
