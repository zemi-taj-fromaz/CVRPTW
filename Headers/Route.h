#ifndef ROUTE_H
#define ROUTE_H

#include "Customer.h"

#include <iostream>
#include <vector>

using namespace std;

class Route {
    private:
    public:
        vector<pair<Customer, int> > order;
        Route();
        double length();
};

#endif
