#pragma once

#include"rtweekend.h"

class Vec3{
    public:
    float x,y,z;
    //constructor
    Vec3(float x=0,float y=0,float z=0) : x(x),y(y),z(z){}

    
    //operators
    Vec3 operator+(Vec3 const& other) const{
        return Vec3(x+other.x,y+other.y,z+other.z);
    }
    Vec3 operator-(Vec3 const& other) const{
        return Vec3(x-other.x,y-other.y,z-other.z);
    }
    Vec3 operator*(float scalar) const{
        return Vec3(x*scalar,y*scalar,z*scalar);
    }
    Vec3 operator*(Vec3 v)const{
        return Vec3(x*v.x,y*v.y,z*v.z);
    }
    Vec3 operator/(float scalar) const{
        return Vec3(x/scalar,y/scalar,z/scalar);
    }
    Vec3 operator-() const{
        return Vec3(-1*x,-1*y,-1*z);
    }
    float& operator[](int index){
        if(index==0) return x;
        else if(index==1) return y;
        else if(index==2) return z;
        else throw std::out_of_range("Only 0,1,2 allowed");
    }

    //methods
    float length() const{
        return sqrt(x*x+y*y+z*z);
    }
    Vec3 unit() const{
        if(length()==0) return *this;
        return (*this)/length();
    }
    float dot(const Vec3& other) const{
        return ((x*other.x)+(y*other.y)+(z*other.z));
    }
    Vec3 cross(const Vec3& other) const{
        return Vec3((y*other.z)-(other.y*z),(other.x*z)-(x*other.z),(x*other.y)-(other.x*y));
    }
    Vec3 reflect(const Vec3& normal) const{
        Vec3 n=normal.unit();
        float mag=dot(n);
        return ((*this)-n*(2*mag));
    }
    Vec3 refract(const Vec3& normal, float refractive_index) const{
        Vec3 n=normal.unit();
        Vec3 incident=(*this).unit();
        if(incident.dot(n)==0){
            if(refractive_index<=1) return incident;
        }
        if(incident.dot(n)>0){
            n=-n;
            refractive_index=1.0f/refractive_index;
        }
        Vec3 PerpToNormal=((n.cross(incident)).cross(n)).unit();
        Vec3 ParaToNormal=-n;
        float NewSinTheta=(fabs((incident.cross(n)).length()))/refractive_index;
        if(NewSinTheta>1){
            return reflect(normal);
        }
        float NewCosTheta=sqrt(1.0f-NewSinTheta*NewSinTheta);
        return (ParaToNormal*NewCosTheta + PerpToNormal*NewSinTheta);
    }

    bool near_zero() const{
        auto s=1e-8;
        return (std::fabs(x)<s) && (std::fabs(y)<s) && (std::fabs(z)<s);
    }

    static Vec3 random(){
        return Vec3(random_double(),random_double(),random_double());
    }
    
    static Vec3 random(double min, double max){
        return Vec3(random_double(min,max),random_double(min,max),random_double(min,max));
    }

};

inline Vec3 random_unit_vector(){
    while(true){
        auto p=Vec3::random(-1,1);
        auto lensq=p.dot(p);
        if(1e-160<lensq && lensq<=1){
            return p/lensq;
        }
    }
}

inline Vec3 random_on_hemisphere(const Vec3& normal){
    auto on_unit_sphere=random_unit_vector();
    if(on_unit_sphere.dot(normal)>0.0){
        return on_unit_sphere;
    }
    else{
        return on_unit_sphere*(-1);
    }
}

inline Vec3 random_in_unit_disk(){
    while(true){
        auto p=Vec3(random_double(-1,1),random_double(-1,1),0);
        if(p.dot(p)<1){
            return p;
        }
    }
}

std::istream& operator>>(std::istream& is, Vec3& v){
    is >> v.x >> v.y >> v.z;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v){
    os<<'('<<v.x<<" "<<v.y<<" "<<v.z<<')';
    return os;
}