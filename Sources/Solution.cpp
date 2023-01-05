#include "../Headers/Solution.h"
#include <math.h>

using namespace std;

Solution::Solution(){
    this->routes.clear();
}

Solution::Solution(vector<Route> routes){
    this->routes = routes;
}

double Solution::distance(){
    double distance = 0.0;
    for(auto route : routes) distance += route.length();
    return distance;
}

void Solution::addRoute(Route route){
    routes.push_back(route);
}

void Solution::print(){
    printf("%d\n", routes.size());
    for (int i = 0; i < routes.size(); i++){
        printf("%d: ", i + 1);
        
        vector<pair<Customer, int> > order = routes[i].order;
        for (int j = 0; j < order.size(); j++){
            printf("%d(%d)", order[j].first.getId(), order[i].second);
            if(j != order.size() - 1) printf("->");
            else printf("\n");
        }
    }
    printf("%2lf\n", distance());
}
