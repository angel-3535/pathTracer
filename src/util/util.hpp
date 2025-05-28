#pragma once

#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <util/types.hpp>
#include <glm/gtx/norm.hpp>

const f64 infinity{std::numeric_limits<f64>::infinity()};
const f64 pi{3.1415926535897923385};

inline f64 DegreeToRadians(f64 degrees) { return degrees * pi / 180.0; }

inline f64 Randomf64() { return std::rand() / (RAND_MAX + 1.0); }

inline f64 Randomf64(f64 min, f64 max) {
  return min + (max - min) * Randomf64();
}
inline static vec3 Randomv3(){
  return vec3(Randomf64(),Randomf64(),Randomf64());
}
inline static vec3 Randomv3(f64 min, f64 max){
  return vec3(Randomf64(min,max),Randomf64(min,max),Randomf64(min,max));
}

inline vec3 RandomUnitv3(){
  while (true) {
    vec3 p = Randomv3(-1,1);
    f64 lensq  = glm::length2(p);
    if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
  }
}

inline vec3 RandomOnHemisphere(const vec3& normal){
  vec3 on_unit_sphere = RandomUnitv3();
  if(dot(on_unit_sphere, normal)>0.0){
    return on_unit_sphere;
  }else {
    return -on_unit_sphere;
  }
}

bool Isv3NearZero(const vec3& v){
  f64 s= 1e-8;
  return (std::fabs(v[0] < s) &&std::fabs(v[1] < s) &&std::fabs(v[2] < s) );
}


#include <interval.h>
#include <ray.h>
