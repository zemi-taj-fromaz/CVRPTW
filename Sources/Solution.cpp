#include "../Headers/Solution.h"
#include <math.h>

using namespace std;

Solution::Solution(int capacity){
    this->routes.clear();
    this->capacity = capacity;
}

bool Solution::CompareByReadyTime(Customer a, Customer b){
    return a.getReadyTime() < b.getReadyTime();
}

bool Solution::CompareById(Customer a, Customer b){
    return a.getId() < b.getId();
}


Solution::Solution(vector<Route> routes, int capacity){
    this->routes = routes;
    this->capacity = capacity;
}

double Solution::length(){
    double distance = 0.0;
    for(auto route : routes) distance += route.length();
    return distance;
}

void Solution::addRoute(Route route){
    routes.push_back(route);
}



void Solution::__greedy__(vector<Customer> customers,Customer depot){
    sort(customers.begin(), customers.end(), CompareByReadyTime);

    for(int i = 0; i < customers.size(); i++){

        //calculate the most optimal route to add to
        //{ {distance_from_route, insertion_point} , route_index}
        vector< pair< pair<double,int>, int> > optimal_routes; 
        for(int j = 0; j < routes.size(); j++){

            optimal_routes.push_back({routes[j].distanceFromRoute(customers[i]), j});

        }
        sort(optimal_routes.begin(), optimal_routes.end());
        bool addedToRoute = false;
        for(auto optimal_route : optimal_routes){
            int insertion_point = optimal_route.first.second;
            int route_index = optimal_route.second;
            bool addedToRoute = routes[route_index].addToRoute(customers[i] , insertion_point);
            if(addedToRoute) break;
        }

        if(addedToRoute == false){
            Route newRoute({depot,customers[i]}, capacity);
            routes.push_back(newRoute);
        }

    }

//     while(!customers.empty()){
        

//         bool added = false;
        
//         for(int i = 0; i < customers.size(); i++){
//             int visit_time = last.second + last.first.getServiceTime() + (int) ceil(last.first.distance(customers[i]));
//             if(visit_time <= customers[i].getDueDate()){
//                 route.order.push_back({customers[i], max(visit_time, customers[i].getReadyTime())});
//                 customers.erase(customers.begin() + i);
//                 added = true;
//                 break;
//             }
//         }
//         if(added) continue;
//         solution.addRoute(route);
//         route = Route();
//     }
// }
}

void Solution::print(){
    printf("%d\n", routes.size());
    for (int i = 0; i < routes.size(); i++){

        printf("%d: ", i + 1);
        double time = 0;

        vector<Customer> order = routes[i].order;
        for (int j = 1; j < order.size(); j++){
            time += order[j].distance(order[j-1]);
            if(time < order[j].getReadyTime()) time = order[j].getReadyTime();
            printf("%d(%d)", order[j].getId(), time);
            time+=order[j].getServiceTime();
            if(j != order.size() - 1) printf("->");
            else printf("\n");
        }
    }
    printf("%2lf\n", length());
}
