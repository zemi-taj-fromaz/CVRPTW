#ifndef GiftWrapper_H
#define GiftWrapper_H
#include <iostream>
#include <vector>

#include "Customer.h"

using namespace std;

class GiftWrapper {
    private:
    public:
        GiftWrapper();
        int orientation(Customer,Customer,Customer);
        vector<Customer> wrap(vector<Customer>);
};

#endif