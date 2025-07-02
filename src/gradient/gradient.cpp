#include <iostream>
#include <stdlib.h>

#include "color.h"
#include "gradient.h"

// g++ main.cpp common/color.cpp src/gradient/gradient.cpp -o output/gradient

void generate_gradient(std::ostream& out) {

    char gradient;

    // Image 
    int i_width = 256;
    int i_height = 256;

    out << "P3\n" << i_width << " " << i_height << "\n255\n";

    // Render

    for (int i=0; i < i_width; i++) {
        std::clog << "\rScanlines remaining: " << (i_width - i) << ' ' << std::flush;
        for (int j=0; j < i_height; j++) {
            double r = double(i) / (i_height-1);
            double g = double(j) / (i_width-1);
            double b = 0.4;

            color pixelcolor = color(r,g,b);
            write_color(out, pixelcolor);
        }
    }
    std::clog << "\rDone.                 \n";

}