#pragma once

#include "glm/geometric.hpp"
#include "util.hpp"
#include <glm/gtx/norm.hpp>

using glm::reflect;
using glm::refract;
using glm::normalize;

inline static vec3 Randomv3() {
  return vec3(Randomf64(), Randomf64(), Randomf64());
}
inline static vec3 Randomv3(f64 min, f64 max) {
  return vec3(Randomf64(min, max), Randomf64(min, max), Randomf64(min, max));
}

inline vec3 RandomUnitv3() {
  while (true) {
    vec3 p = Randomv3(-1, 1);
    f64 lensq = glm::length2(p);
    if (1e-160 < lensq && lensq <= 1)
      return p / sqrt(lensq);
  }
}

inline vec3 RandomOnHemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = RandomUnitv3();
  if (dot(on_unit_sphere, normal) > 0.0) {
    return on_unit_sphere;
  } else {
    return -on_unit_sphere;
  }
}

inline bool Isv3NearZero(const vec3 &v) {
  f64 s = 1e-8;
  return (std::fabs(v[0] < s) && std::fabs(v[1] < s) && std::fabs(v[2] < s));
}
