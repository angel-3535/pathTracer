#pragma once

#include "glm/geometric.hpp"
#include "hittable.h"
#include "interval.h"
#include <util.hpp>

class Sphere : public Hittable {
public:
  Sphere(const point3 &center, f64 radius)
      : center(center), radius(std::fmax(0, radius)) {}
  bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override {
    vec3 oc = center - r.origin();
    f64 a = glm::dot(r.direction(), r.direction());
    f64 h = glm::dot(r.direction(), oc);
    f64 c = glm::dot(oc, oc) - radius * radius;
    f64 discriminant = h * h - a * c;
    if (discriminant < 0) {
      return false;
    }
    f64 sqrtd = std::sqrt(discriminant);

    f64 root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
      root = (h + sqrtd) / a;
      if (!ray_t.surrounds(root))
        return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.SetFaceNoral(r, outward_normal);

    return true;
  }

private:
  point3 center;
  f64 radius;
};
