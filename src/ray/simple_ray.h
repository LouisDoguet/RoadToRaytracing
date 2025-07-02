#ifndef SIMPLE_RAY
#define SIMPLE_RAY

#include "ray.h"
#include "color.h"

color ray_color(const ray& r);
void generate_rayimage(std::ostream& out);

#endif