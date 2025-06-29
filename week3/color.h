#pragma once

#include"vec3.h"
#include"rtweekend.h"

using color=Vec3;

void write_color(const color& pixel_color){
    auto r=pixel_color.x;
    auto g=pixel_color.y;
    auto b=pixel_color.z;

    int rint=int(255.999*r);
    int gint=int(255.999*g);
    int bint=int(255.999*b);

    std::cout<<rint<<' '<<gint<<' '<<bint<<'\n';
};