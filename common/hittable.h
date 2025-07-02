#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

class material;

class hit_record {
    public:
        point3 p;
        vec3 normal;
        bool front_face;
        shared_ptr<material> mat;
        double t;

    void set_normal_face(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
    public :
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {};
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            double temp_closest = ray_t.max;

            for (const shared_ptr<hittable>& object : objects) {
                if (object->hit(r, interval(ray_t.min, temp_closest), temp_rec)) {
                    hit_anything = true;
                    temp_closest = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }

};

#endif