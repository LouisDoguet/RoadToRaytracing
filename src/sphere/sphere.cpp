#include <iostream>
#include "color.h"
#include "src_sphere.h"

/* COMPILE :
g++ -Icommon -Isrc/sphere  main.cpp common/color.cpp src/ray/sphere.cpp -o output/simple_ray
*/

double hit_shpere(const point3& center, double radius, const ray& r) {

    vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius*radius;
    double discr = h*h - a*c;

    if (discr < 0){
        return -1.0;
    } else {
        return (h - std::sqrt(discr) ) / a;
    }
    return (discr>=0.0);
}

color ray_color(const ray& r) {
    double t = hit_shpere(point3(0.0,0.0,-1.0), 0.5, r);
    vec3 unit_direction = unit_vector(r.direction());
    if (t > 0.0){
        vec3 N = unit_vector( r.at(t) - vec3(0.0,0.0,-1.0) );
        double dir = VEC_3::dot(vec3(0,0,1), N);
        return dir*dir * color(1,1,1);
    }
    return color(0.1,0.1,0.1);
}

void generate_rayimage(std::ostream& out) {

    // Image size

    double aspect_ratio = 16.0/9.0;
    int image_width = 2000;

    int image_height = int(image_width / aspect_ratio); // Computes thanks to AR
    image_height = (image_height < 1) ? 1 : image_height; // If image_height less than 1

    // Viewport : Screen with pixels
    // Size of it, in reality

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Camera 

    auto focal_length = 1; // Distance between cam and viewport
    auto camera_center = point3(0,0,0);

    // Vector defining the horizontal|vertical side of viewport

    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);

    // Pixel horizontal/vertical vectors

    vec3 pixel_du = viewport_u / image_width;
    vec3 pixel_dv = viewport_v / image_height;

    // From cam to first pixel of viewport

    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_du + pixel_dv);


    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            vec3 pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

}