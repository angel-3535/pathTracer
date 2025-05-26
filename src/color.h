#pragma once

#include <util.hpp>

inline std::ostream &operator<<(std::ostream &stream,
                                const color &pixel_color) {

  icolor icolor =
      vec3(i32(255.999 * pixel_color.r), i32(255.999 * pixel_color.g),
           i32(255.999 * pixel_color.b));

  stream << icolor.r << ' ' << icolor.g << ' ' << icolor.b << '\n';

  return stream;
}
