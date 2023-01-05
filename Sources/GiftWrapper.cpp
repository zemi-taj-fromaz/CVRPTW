#include "../Headers/GiftWrapper.h"

GiftWrapper::GiftWrapper(){

}

int GiftWrapper::orientation(Customer p, Customer q, Customer r){

    int val = (q.getCoord().second - p.getCoord().second) * (r.getCoord().first - q.getCoord().first) - (q.getCoord().first - p.getCoord().first) * (r.getCoord().second - q.getCoord().second);

    if (val == 0) return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise

}

vector<Customer> GiftWrapper::wrap(vector<Customer> customers){

    int n = customers.size();

    if (n < 3) return customers;

    vector<int> next(n,-1);
    int l = 0;

    for (int i = 1; i < n; i++){
        if (customers[i].getCoord().first < customers[l].getCoord().first) l = i;
    }

    int p = l, q;

    do{
        q = (p + 1) % n;

        for (int i = 0; i < n; i++){
            if (this->orientation(customers[p], customers[i], customers[q]) == 2) q = i;
        }

        next[p] = q; // Add q to result as a next Customer of p
        p = q; // Set p as q for next iteration
    }while (p != l);

    vector<Customer> ret;

    for (int i = 0; i < n; i++){
        if (next[i] != -1) ret.push_back(customers[i]);
    }
    return ret;
}