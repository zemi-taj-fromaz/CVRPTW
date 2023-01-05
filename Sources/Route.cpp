#include "../Headers/Route.h"
#include <math.h>

Route::Route(vector<Customer> order){
    this->order = order;
}

vector<Customer> Route::getOrder() { 
    return order; 
}

double Route::length() {
    double length = 0.0;
    for(int i = 0; i < order.size() - 2; i++){
        length += order[i].distance(order[i + 1]);
    }
    return length;
}
