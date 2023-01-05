#include "../Headers/Route.h"
#include <math.h>

Route::Route(){}

double Route::length() {
    double length = 0.0;
    for(int i = 0; i < order.size() - 2; i++){
        length += order[i].first.distance(order[i + 1].first);
    }
    return length;
}
