#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <util/types.hpp>

const f64 infinity{std::numeric_limits<f64>::infinity()};
const f64 pi{3.1415926535897923385};

inline f64 DegreeToRadians(f64 degrees) { return degrees * pi / 180.0; }

inline f64 Randomf64() { return std::rand() / (RAND_MAX + 1.0); }

inline f64 Randomf64(f64 min, f64 max) {
  return min + (max - min) * Randomf64();
}



#include <interval.h>
#include <ray.h>
