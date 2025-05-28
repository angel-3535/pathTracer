#pragma once

#include "interval.h"
#include <util.hpp>

class Material;

class HitRecord{
  public:
    point3 p;
    vec3 normal;
    std::shared_ptr<Material> mat;
    f64 t;
    bool front_face;

  //NOTE: outward_normal is unit length
  void SetFaceNoral(const Ray& r, const vec3& outward_normal){
    front_face = glm::dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal: -outward_normal;
  }
};

class Hittable{
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray& r,Interval ray_t, HitRecord& rec) const = 0;
};



