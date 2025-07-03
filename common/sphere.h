/*
Sphere objects definition
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "interval.h"

// Using of the type vec3 as point3
using point3 = vec3;

// Class shpere, inheriting from hittable
class sphere : public hittable {
    public:
        // -- CONSTRUCTOR --
        sphere(const point3& center, double radius, shared_ptr<material> mat) 
            : center(center), radius(std::fmax(0.0, radius)), mat(mat) {}

        // -- SURCHARGE --
        // From public attribute of the virtual class hittable
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override { // OVERRIDE : prioritize this declaration

            vec3 oc = center - r.origin();
            double a = r.direction().length_squared();
            double h = dot(r.direction(), oc);
            double c = oc.length_squared() - radius*radius;

            double discr = h*h - a*c;
            if (discr < 0)
                return false; // There is no t in P+D*t that hits the sphere

            double sqrtd = std::sqrt(discr);

            double root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {     // If the root is in the interval of research
                root = (h + sqrtd) / a;       // Check for the other root
                if (!ray_t.surrounds(root))   // Nothing found : out of the interval
                    return false;
            }

            rec.t = root; // t value 
            rec.p = r.at(rec.t); // hit position
            vec3 outward_normal = (rec.p - center) / radius; // normal vector at the hit position
            rec.set_normal_face(r, outward_normal); // Inverts vector outward_normal if the sign is not negative
            rec.mat = mat; // Material encoutered

            return true;
        }

    private:

        point3 center; // Sphere center
        double radius; // Sphere radius
        shared_ptr<material> mat; // Sphere material

};


#endif