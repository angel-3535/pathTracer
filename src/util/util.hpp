#pragma once

#include "glm/trigonometric.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <ray.h>

const f64 infinity{std::numeric_limits<f64>::infinity()};
const f64 pi{3.1415926535897923385};


inline f64 DegreeToRadians(f64 degrees){
  return degrees * pi / 180.0;
}

#include <color.h>
#include <ray.h>
#include <util/types.hpp>
#include <interval.h>
