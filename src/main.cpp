#include "types.hpp"
#include <iostream>
#include <util/util.hpp>
#include <color.h>

int main(int argc, char *argv[]) {
  i32 image_width{320};
  i32 image_height{320};

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (u32 h = 0; h < image_height; h++) {
    std::clog << "\rScanlines remaining: " << (image_height - h) << ' ' << std::flush;
    for (u32 w = 0; w < image_width; w++) {
      color color = vec3((f32(w) / (image_width - 1)),
                        (f32(h) / (image_height - 1)), 0.0f);


      std::cout << color;
    }
  }


  std::clog << "\rDone.                 \n";
  return 0;
}
