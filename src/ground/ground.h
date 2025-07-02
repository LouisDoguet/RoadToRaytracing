#ifndef GROUND_H
#define GROUND_H

#include "raytracer.h"

color ray_color(const ray& r, const hittable& world);
void generate_rayimage(std::ostream& out);

#endif