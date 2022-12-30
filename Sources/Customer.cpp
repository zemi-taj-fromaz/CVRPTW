#include "../Headers/Customer.h"

Customer::Customer(pair<int,int> coord,int demand,int ready_time,int due_date,int service_time){
    this->coord = coord;
    this->demand = demand;
    this->ready_time = ready_time;
    this->due_date = due_date;
    this->service_time = service_time;
}

pair<int,int> Customer::getCoord(){
    return {this->coord.first,this->coord.second};
}
int Customer::getDemand(){
    return this->demand;
}

int Customer::getReadyTime(){
    return this->ready_time;
}
int Customer::getDueDate(){
    return this->due_date;
}
int Customer::getServiceTime(){
    return this->service_time;
}

