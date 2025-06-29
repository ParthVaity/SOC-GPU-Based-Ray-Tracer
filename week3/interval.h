#include"rtweekend.h"

class interval{
    public:
    double min;
    double max;
    
    interval():min(+infinity),max(-infinity){}
    interval(double a, double b):min(a),max(b){};

    double size() const{
        return max-min;
    }

    bool contains(double t) const{
        return t>=min && t<=max;
    }

    bool surrounds(double x) const{
        return min<x && x<max;
    }

    static const interval empty, universe;
};

const interval interval::empty=interval(+infinity, -infinity);
const interval interval::universe=interval(-infinity, +infinity);