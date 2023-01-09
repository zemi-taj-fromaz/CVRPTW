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
    public:
        int capacity;
        vector<Route> routes;
        Solution(int);
        Solution(vector<Route>,int);
        void print(string filename,string);
        double length();
        void addRoute(Route);
        void __greedy__(vector<Customer>,Customer);
        static bool CompareById(Customer a, Customer b);
        static bool CompareByReadyTime(Customer a, Customer b);
        int size();
        bool isFeasible(int);
        bool isBetter(Solution other);
};

#endif
