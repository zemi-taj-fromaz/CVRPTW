#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <Route.h>

using namespace std;

class Solution {
    private:
        vector<Route> routes;
    public:
        Solution();
        Solution(vector<Route>);
        void print();
        double distance();
        void addRoute(Route);
};

#endif
