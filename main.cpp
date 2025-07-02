#include <iostream>
#include <fstream>
#include "raytracer.h"

int main(){

    hittable_list world;

    shared_ptr<material> material_center = make_shared<metal>(color(0.5, 0.5, 1));
    shared_ptr<material> material_ground = make_shared<lambertian>(color(0.1, 0.1, 0.1));
    //shared_ptr<material> material_1   = make_shared<lambertian>(color(0.6, 0.07, 0.7));
    shared_ptr<material> material_2   = make_shared<metal>(color(1, 0.2, 0.2));
    //shared_ptr<material> material_3   = make_shared<lambertian>(color(0.4, 0.7, 0));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    //world.add(make_shared<sphere>(point3(-0.2,    0.55, -0.9),   0.1, material_1));
    world.add(make_shared<sphere>(point3(-0.25,    -0.3, -0.7),   0.09, material_2));
    //world.add(make_shared<sphere>(point3(0.23,    0.47, -0.75),   0.15, material_3));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 10000;
    cam.max_depth = 10000;

    cam.render(world);

    return 1;
}