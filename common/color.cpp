#include <iostream>
#include "raytracer.h"

inline double linear_to_gamma(double lin) {
        if (lin>0) {
                return std::sqrt(lin);
        }
        return 0;
}

void write_color(std::ostream& out, const color& pixel_color){

        double r = pixel_color.x();
        double g = pixel_color.y();
        double b = pixel_color.z();

        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        static const interval intensity(0.000, 0.999);
        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}
