#ifndef ROUTE_H
#define ROUTE_H

#include "Customer.h"

#include <iostream>
#include <vector>

using namespace std;

class Route {
    private:
        bool checkConstraints(vector<Customer>);
        int capacity;
    public:
        vector<Customer> order;
        Route(int);
        Route(vector<Customer>,int);
        double length();
        pair<double,int> distanceFromRoute(Customer);
        bool addToRoute(Customer,int);
};

#endif
