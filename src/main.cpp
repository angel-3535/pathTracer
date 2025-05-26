#include "glm/detail/type_vec3.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "ray.h"
#include "types.hpp"
#include <color.h>
#include <iostream>
#include <util/util.hpp>

color RayColor(const Ray &r) {
  vec3 unit_dir = glm::normalize(r.direction());
  f32 a = 0.5f * (unit_dir.y + 1.f);
  return ( 1.f - a ) * color(1.f) + a*color(0.5f,0.7f,1.f);
}

int main(int argc, char *argv[]) {
  f32 aspect_ratio{16.f / 9.f};
  i32 image_width{400};
  i32 image_height{static_cast<i32>(image_width / aspect_ratio)};

  f32 focal_length{1.f};
  f32 viewport_height{2.f};
  f32 viewport_width{viewport_height * (f32(image_width) / image_height)};
  point3 camera_center(0.f, 0.f, 0.f);

  vec3 viewport_u(viewport_width, 0.f, 0.f);
  vec3 viewport_v(0.f, -viewport_height, 0.f);

  vec3 pixel_delta_u = viewport_u / f32(image_width);
  vec3 pixel_delta_v = viewport_u / f32(image_height);

  vec3 viewport_upper_left = camera_center - vec3(0.f, 0.f, focal_length) -
                             viewport_u / 2.f - viewport_v / 2.f;
  vec3 pixel00_loc =
      viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (u32 h = 0; h < image_height; h++) {
    std::clog << "\rScanlines remaining: " << (image_height - h) << ' '
              << std::flush;
    for (u32 w = 0; w < image_width; w++) {
      point3 pixel_center(pixel00_loc + (f32(w) * pixel_delta_u) +
                          (f32(h) * pixel_delta_v));
      vec3 ray_direction(pixel_center - camera_center);
      Ray r(camera_center, ray_direction);

      color color(RayColor(r));
      std::cout << color;
    }
  }

  std::clog << "\rDone.                 \n";
  return 0;
}
