#pragma once

#include <util/types.hpp>

class Ray {
public:
  Ray() {}
  Ray(const point3& origin, const vec3& direction): orig(origin), dir(direction) {}
  const point3& origin() const {return orig;}
  const vec3& direction() const {return dir;}

  inline point3 at(f64 t) const {
    return orig + t*dir;
  }

  ~Ray() {}

private:
  point3 orig;
  vec3 dir;
};
