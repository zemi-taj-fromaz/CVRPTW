#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

class Customer {
    private:
        int id;
        pair<int,int> coord;
        int demand;
        int ready_time;
        int due_date;
        int service_time;
    public:
        Customer(int,pair<int,int>,int,int,int,int);
        int getId();
        pair<int,int> getCoord();
        int getDemand();
        int getReadyTime();
        int getDueDate();
        int getServiceTime();
        double distance(Customer);
        bool operator==(Customer &rhs);
        bool operator<(Customer &rhs);
};

#endif