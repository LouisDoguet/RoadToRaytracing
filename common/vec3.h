/*
VEC IN 3 DIMENSIONS LIBRARY
*/

#ifndef VEC_3
#define VEC_3

#include <cmath>
#include <iostream>

class vec3 {
    public:
        double e[3]; // components

        // -- CONSTRUCTORS --
        vec3() : e{0,0,0} {};
        // Surcharge 1 :
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

        // -- GETTERS --
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        // -- OPERATOR SURCHARGE --
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // New instance : no &
        double operator[](int i) const { return e[i]; } // Listing (const var)
        double& operator[](int i) { return e[i]; } // Listing

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        } // Returns a pointer to the current instance 

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        } // Returns a pointer to the current instance

        vec3& operator/=(double t) {
            return *this *= 1/t;
        } // Returns a pointer to the current instance

        // -- PUBLIC METHODS --

        double length() const {
            return std::sqrt(length_squared());
        } // Generates a new double

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        } // Generates a new double

        // Static methods :
        // Does not require the object

        static vec3 random() { // Refers to random header
            return vec3(random_double(), random_double(), random_double());
        } 
        static vec3 random(double min, double max) { // Surcharge
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions.
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

};

// -- OUTER SURCHARGE --

// Dataflux surcharge
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
} // Returns a new instance

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
} // Returns a new instance

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
} // Returns a new instance
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
} // Returns a new instance
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
} // Returns a new instance

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
} // Returns a new instance

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
} // Returns a new instance

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}


// -- FUNCTIONS --


inline vec3 unit_vector(const vec3& v) {
    return v / v.length(); // Uses the / surcharged operator to normalize
}

inline vec3 random_unit_vector() {
    // Returns a random vector in the unit cirle
    while (true)
    {
        vec3 p = vec3::random(-1,1); // Call of a static function
        double lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_in_unit_disk() {
    // Returns a random vector in the unit disk
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    // Returns a random vector in the same hemisphere as the normal vector in input
    vec3 rnd_unit = random_unit_vector();
    if (dot(rnd_unit, normal) > 0.0) {
        return rnd_unit;
    } else {
        return -rnd_unit;
    }
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    // Reflexion equation
    return v - 2*dot(v,n)*n;
}


inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    // Refraction equation
    // Complicated because optimized, see BOOK 1
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif