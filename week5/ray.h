#pragma once

#include<iostream>
#include"vec3.h"

using point3=Vec3;

class ray{
    public:
    point3 orig;
    Vec3 dir;

    ray(){}
    ray(const point3& origin, const Vec3& direction) : orig(origin),dir(direction){}

    point3 at(double t) const {return (orig + dir*double(t));}
};