#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <vector>
#include <Customer.h>

using namespace std;

class Route {
    private:
        vector<Customer> order;
    public:
        Route(vector<Customer>);
        vector<Customer> getOrder();
        double distance();
};

#endif
