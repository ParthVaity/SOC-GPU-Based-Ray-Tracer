
#pragma once

#include"hittable.h"
#include"material.h"

class camera{
    public:

    double aspect_ratio=1.0;
    int img_width=100;
    int samples_per_pixel=100;
    int max_depth=10;

    double vfov=90;
    point3 lookfrom=point3(0,0,0);
    point3 lookat=point3(0,0,-1);
    Vec3 vup=Vec3(0,1,0);

    double defocus_angle=0;
    double focus_dist=10;

    void render(const hittable& world){
        initialise();

        std::cout<<"P3\n"<<img_width<<' '<<img_height<<"\n255\n";

        for(int j=0;j<img_height;j++){
            std::clog<<"\rScanlines remaining: "<<(img_height-j)<<' '<<std::flush;
            for(int i=0;i<img_width;i++){
                color pixel_color(0,0,0);
                for(int sample=0;sample<samples_per_pixel;sample++){
                    ray r=get_ray(i,j);
                    pixel_color=pixel_color+ray_color(r,max_depth,world);
                }
                write_color(pixel_color*pixel_samples_scale);
            }
        }
        std::clog<<"\rDone.                 \n";
    }

    private:
    
    int img_height;
    double pixel_samples_scale;
    point3 camera_centre;
    point3 pixel_origin;
    Vec3 delta_u;
    Vec3 delta_v;
    Vec3 u,v,w;
    Vec3 defocus_disk_u;
    Vec3 defocus_disk_v;

    void initialise(){
        img_height=int(img_width/aspect_ratio);
        img_height=(img_height<1)?1:img_height;

        pixel_samples_scale=1.0/samples_per_pixel;

        camera_centre=lookfrom;

        auto theta=degrees_to_radians(vfov);
        auto h=std::tan(theta/2);
        auto viewport_height=2.0*h*focus_dist;
        auto viewport_width=viewport_height*(double(img_width)/img_height);

        w=(lookfrom-lookat).unit();
        u=(vup.cross(w)).unit();
        v=w.cross(u);

        auto viewport_u=u*viewport_width;
        auto viewport_v=(-v)*viewport_height;
        delta_u=viewport_u/img_width;
        delta_v=viewport_v/img_height;

        auto viewport_origin=camera_centre-(w*focus_dist)-viewport_u/2- viewport_v/2;
        pixel_origin=viewport_origin+(delta_u+delta_v)*0.5;

        auto defocus_r=focus_dist*std::tan(degrees_to_radians(defocus_angle/2));
        defocus_disk_u=u*defocus_r;
        defocus_disk_v=v*defocus_r;
    }

    ray get_ray(int i,int j) const{
        auto offset=sample_square();
        auto pixel_sample=pixel_origin+(delta_u*(i+offset.x))+(delta_v*(j+offset.y));
        auto ray_origin=(defocus_angle<=0) ? camera_centre : defocus_disk_sample();
        auto ray_direction=pixel_sample-ray_origin;

        return ray(ray_origin,ray_direction);
    }

    Vec3 sample_square() const{
        return Vec3(random_double()-0.5,random_double()-0.5,0);
    }

    point3 defocus_disk_sample() const{
        auto p=random_in_unit_disk();
        return (camera_centre+(defocus_disk_u*(p.x))+(defocus_disk_v*(p.y)));
    }

    color ray_color(const ray& r,int depth , const hittable& world){
        hit_record rec;
        if(depth<=0)return color(0,0,0);

        if(world.hit(r,interval(0.001,infinity),rec)){
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r,rec,attenuation,scattered)){
                return attenuation*ray_color(scattered,depth-1,world);
            }
            return color(0,0,0);
        }

        Vec3 unit_direction=r.dir.unit();
        auto a=0.5*(unit_direction.y+1.0);
        return color(1,1,1)*(1.0-a)+color(0.5,0.7,1.0)*a;
    }

};