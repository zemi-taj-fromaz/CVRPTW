#ifndef ROUTE_H
#define ROUTE_H

#include "Customer.h"

#include <iostream>
#include <vector>

using namespace std;

class Route {
    private:
        int capacity;
    public:
        vector<Customer> order;
        vector<pair<Customer, int> > order_with_time;
        Route(int);
        Route(vector<Customer>,int);
        double length();
        pair<double,int> distanceFromRoute(Customer);
        bool addToRoute(Customer,int);
        void removeRoute(int);
        bool checkConstraints();
        void orderFromOWT();
        void OWTFromOrder();
};

#endif
