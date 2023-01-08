#ifndef SOLUTION_H
#define SOLUTION_H

#include "../Sources/Route.cpp"

#include <iostream>
#include <vector>
#include <string>
#include "Route.h"

using namespace std;

class Solution {
    private:
        int capacity;
        vector<Route> routes;
    public:
        Solution(int);
        Solution(vector<Route>,int);
        void print(string filename);
        double length();
        void addRoute(Route);
        void __greedy__(vector<Customer>,Customer);
        static bool CompareById(Customer a, Customer b);
        static bool CompareByReadyTime(Customer a, Customer b);
        int size();
};

#endif
