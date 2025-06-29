#include"rtweekend.h"
#include"hittable.h"
#include"hittablelist.h"
#include"sphere.h"

color ray_color(const ray& r, const hittable& world){
    hit_record rec;
    if(world.hit(r,interval(0,infinity),rec)){
        return (rec.normal+color(1,1,1))*0.5;
    }
    Vec3 unit_direction=r.dir.unit();
    auto a=0.5*(unit_direction.y+1.0);
    return color(1,1,1)*(1.0-a)+color(0.5,0.7,1.0)*a;
}

int main(){

    auto ratio=16.0/9.0;
    int img_width=1600;
    int img_height=int(img_width*9.0/16.0);
    img_height=(img_height<1)?1:img_height;

    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100));

    auto focal_length=1.0;
    auto viewport_height=2.0;
    auto viewport_width=viewport_height*(double(img_width)/img_height);
    auto camera_centre=point3(0,0,0);

    auto viewport_u=Vec3(viewport_width,0,0);
    auto viewport_v=Vec3(0,-viewport_height,0);
    auto delta_u=viewport_u/img_width;
    auto delta_v=viewport_v/img_height;

    auto viewport_origin=camera_centre-Vec3(0,0,focal_length)-viewport_u/2- viewport_v/2;
    auto pixel_origin=viewport_origin+(delta_u+delta_v)*0.5;

    std::cout<<"P3\n"<<img_width<<' '<<img_height<<"\n255\n";

    for(int j=0;j<img_height;j++){
        for(int i=0;i<img_width;i++){
            auto pixel_center=pixel_origin+(delta_u*i)+(delta_v*j);
            auto ray_dir=pixel_center-camera_centre;
            ray r(camera_centre,ray_dir);
            color pixel_color=ray_color(r,world);
            write_color(pixel_color);
        }
    }
}