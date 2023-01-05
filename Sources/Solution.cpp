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
        
        vector<Customer> order = routes[i].getOrder();
        int service_time = 0;
        for (int j = 0; j < order.size(); j++){
            if(j != 0){
                service_time = service_time + order[j - 1].getServiceTime() + (int) ceil(order[j].distance(order[j - 1]));
                service_time = max(service_time, order[j].getReadyTime());
            }
            printf("%d(%d)", order[j].getId(), service_time);
            if(j != order.size() - 1) printf("->");
            else printf("\n");
        }
    }
    printf("%2lf\n", distance());
}
