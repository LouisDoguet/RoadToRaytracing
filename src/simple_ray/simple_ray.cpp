#include <iostream>
#include "color.h"
#include "simple_ray.h"

/* COMPILE :
g++ -Icommon -Isrc/ray  main.cpp common/color.cpp src/ray/simple_ray.cpp -o output/simple_ray
*/

double hit_shpere(const point3& center, double radius, const ray& r) {

    vec3 oc = center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), oc);
    double c = dot(oc,oc) - radius*radius;
    double discr = b*b - 4.0*a*c;

    return (discr>=0.0);
}

color ray_color(const ray& r) {

    if (hit_shpere(point3(0.0,0.0,-1.0), 0.5, r)){
        return color(1.0,0.0,0.0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.x() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.1, 0.5, 0.9);
}

void generate_rayimage(std::ostream& out) {

    // Image size

    double aspect_ratio = 16.0/9.0;
    int image_width = 1240;

    int image_height = int(image_width / aspect_ratio); // Computes thanks to AR
    image_height = (image_height < 1) ? 1 : image_height; // If image_height less than 1

    // Viewport : Screen with pixels
    // Size of it, in reality

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Camera 

    auto focal_length = 1.0; // Distance between cam and viewport
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