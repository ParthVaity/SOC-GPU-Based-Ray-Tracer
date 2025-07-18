#pragma once

#include<iostream>
#include"rtweekend.h"

class hit_record{
    public:
    point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const Vec3& outward_normal){
        //This sets the normal for hit record,ensuring it is opposite to ray direction
        //outward_normal should be unit vector
        front_face=r.dir.dot(outward_normal)<0;
        normal=front_face?outward_normal:-outward_normal;
    }
};

class hittable{
    public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};