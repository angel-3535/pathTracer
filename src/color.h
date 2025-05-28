#pragma once

#include <util.hpp>

inline std::ostream &operator<<(std::ostream &stream,
                                const color &pixel_color) {

  static const Interval intensity(0.000, 0.999);
  icolor icolor(
      i32(256 * intensity.clamp(pixel_color.r)),
      i32(256 * intensity.clamp(pixel_color.g)),
      i32(256 * intensity.clamp(pixel_color.b))
  );

  stream << icolor.r << ' ' << icolor.g << ' ' << icolor.b << '\n';

  return stream;
}
