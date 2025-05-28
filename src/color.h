#pragma once

#include <random>
#include <util.hpp>

inline f64 LinearToGamma(f64 linear_component){
  if (linear_component > 0) {
    return std::sqrt(linear_component);
  }
  return 0;
}

inline std::ostream &operator<<(std::ostream &stream,
                                const color &pixel_color) {

  color temp_color(
      LinearToGamma(pixel_color.r),
      LinearToGamma(pixel_color.g),
      LinearToGamma(pixel_color.b)
      );

  static const Interval intensity(0.000, 0.999);
  icolor icolor(
      i32(256 * intensity.clamp(temp_color.r)),
      i32(256 * intensity.clamp(temp_color.g)),
      i32(256 * intensity.clamp(temp_color.b))
  );


  stream << icolor.r << ' ' << icolor.g << ' ' << icolor.b << '\n';

  return stream;
}
