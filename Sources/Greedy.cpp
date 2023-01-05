// #include "Route.cpp"
// #include "Customer.cpp"
// #include "Solution.cpp"

// #include <algorithm>
// #include <math.h>
// #include <vector>

// bool CompareByReadyTime(Customer a, Customer b){
//     return a.getReadyTime() < b.getReadyTime();
// }

// bool CompareById(Customer a, Customer b){
//     return a.getId() < b.getId();
// }

// Solution Greedy(vector<Customer> customers, Customer depot){
//     Solution solution;
//     Route route;

//     sort(customers.begin(), customers.end(), CompareByReadyTime);

//     while(!customers.empty()){
//         if(route.order.empty()) route.order.push_back({depot, 0});
        
//         pair<Customer, int> last = route.order[route.order.size() - 1];

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

//     return solution;
// }
