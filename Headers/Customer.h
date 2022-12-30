#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

class Customer {
    private:
        pair<int,int> coord;
        int demand;
        int ready_time;
        int due_date;
        int service_time;
    public:
        Customer(pair<int,int>,int,int,int,int);
        pair<int,int> getCoord();
        int getDemand();
        int getReadyTime();
        int getDueDate();
        int getServiceTime();
};

#endif