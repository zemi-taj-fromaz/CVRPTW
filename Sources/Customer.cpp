#include "../Headers/Customer.h"
#include <math.h>

Customer::Customer(int id,pair<int,int> coord,int demand,int ready_time,int due_date,int service_time){
    this->id = id;
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

double Customer::distance(Customer other){
    return sqrt(pow((coord.first - other.getCoord().first), 2) + pow(coord.second - other.getCoord().second, 2));
}

bool Customer::operator==(Customer& rhs){
    return this->id == rhs.getId();
}
