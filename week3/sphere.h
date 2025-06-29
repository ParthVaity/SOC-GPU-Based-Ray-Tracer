#pragma once

#include"rtweekend.h"

class sphere : public hittable {
    private:
    point3 center;
    double radius;
    
    public:
    
    sphere(const point3& center, double radius):center(center),radius(fmax(radius,0)){}
    
    bool hit(const ray&r, interval ray_t, hit_record& rec) const override{
        Vec3 oc=center-r.orig;
        auto a=r.dir.dot(r.dir);
        auto h=r.dir.dot(oc);
        auto c=oc.dot(oc)-radius*radius;
        auto discriminant=h*h-a*c;
        if(discriminant<0) return false;
        auto sqrtd=sqrt(discriminant);
        auto root=(h-sqrtd)/a;
        if(!ray_t.surrounds(root)){
            root=(h+sqrtd)/a;
            if(!ray_t.surrounds(root)) return false;
        }
        rec.t=root;
        rec.p=r.at(rec.t);
        Vec3 outward_normal=(rec.p-center)/radius;
        rec.set_face_normal(r,outward_normal);

        return true;
    }
};