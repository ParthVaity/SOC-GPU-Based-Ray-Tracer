#pragma once

#include<iostream>
#include<cmath>
#include<limits>
#include<memory>
#include<cstdlib>
#include<random>

using std::shared_ptr;
using std::make_shared;

const double infinity=std::numeric_limits<double>::infinity();
const double pi=3.1415926535897932385;

inline double degrees_to_radians(double degrees){
    return degrees*pi/180.0;
}

inline double random_double(){
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max){
    return min+((max-min)*random_double());
}

#include"vec3.h"
#include"ray.h"
#include"color.h"
#include"interval.h"
#include"hittable.h"
#include"hittablelist.h"
#include"sphere.h"