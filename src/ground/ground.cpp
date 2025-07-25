#include <iostream>
#include "ground.h"

hittable_list WORLD;
vec3 X = vec3(0,0,1);

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0,infinity), rec)) {
        double dir = dot(X,rec.normal);
        return dir*dir * color(1,1,1);
    }

    return color(0.2,0.2,0.2);
}

void generate_rayimage(std::ostream& out) {

    // Image size

    double aspect_ratio = 16.0/9.0;
    int image_width = 600;

    int image_height = int(image_width / aspect_ratio); // Computes thanks to AR
    image_height = (image_height < 1) ? 1 : image_height; // If image_height less than 1

    // Viewport : Screen with pixels
    // Size of it, in reality

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // Camera 

    WORLD.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    WORLD.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

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

            color pixel_color = ray_color(r, WORLD);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\r";

}