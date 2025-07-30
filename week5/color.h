#pragma once

#include"vec3.h"
#include"rtweekend.h"
#include"interval.h"

using color=Vec3;

inline double linear_to_gamma(double linear_component){
    if(linear_component>0) return std::sqrt(linear_component);
    return 0;
};

void write_color(const color& pixel_color){
    auto r=pixel_color.x;
    auto g=pixel_color.y;
    auto b=pixel_color.z;

    r=linear_to_gamma(r);
    g=linear_to_gamma(g);
    b=linear_to_gamma(b);

    static const interval intensity(0.000,0.999);
    int rint=int(255.999*intensity.clamp(r));
    int gint=int(255.999*intensity.clamp(g));
    int bint=int(255.999*intensity.clamp(b));

    std::cout<<rint<<' '<<gint<<' '<<bint<<'\n';
};