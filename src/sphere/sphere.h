#ifndef SIMPLE_RAY
#define SIMPLE_RAY

#include "ray.h"
#include "color.h"

double hit_shpere(const point3& center, double radius, const ray& r);
color ray_color(const ray& r);
void generate_rayimage(std::ostream& out);

#endif