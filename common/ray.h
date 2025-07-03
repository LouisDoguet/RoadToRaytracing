#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Using the name point3 to refer to vec3 instances
using point3 = vec3;

class ray {
    public:
        // -- CONSTRUCTORS --
        ray() {};
        // Surcharge
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {};

        // -- GETTERS --
        const point3& origin() const { return orig; };
        const vec3& direction() const { return dir; };

        point3 at(double t) const {
            // Returns the position at t
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif