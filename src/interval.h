#pragma once
#include <util.hpp>

class Interval {
public:
  f64 min, max;

public:
  Interval() : min(+infinity), max(-infinity) {}
  Interval(f64 min, f64 max) : min(min), max(max) {}
  ~Interval() = default;

  f64 size() const { return max - min; }

  bool contains(f64 x) const { return min <= x && x <= max; }

  bool surrounds(f64 x) const { return min < x && x < max; }

  f64 clamp(f64 x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
  }

  static const Interval empty, universe;

};


const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
