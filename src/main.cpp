#include "glm/detail/type_vec3.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/geometric.hpp"
#include "ray.h"
#include "types.hpp"
#include <color.h>
#include <iostream>
#include <util/util.hpp>

f64 HitSphere(const point3 &center, f32 radius, const Ray &r) {
  vec3 oc = center - r.origin();
  f64 a = glm::dot(r.direction(), r.direction());
  f64 b = -2.0 * glm::dot(r.direction(), oc);
  f64 c = glm::dot(oc, oc) - radius * radius;
  f64 discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return ((-b - std::sqrt(discriminant)) / (2.0 * a));
  }
}

color RayColor(const Ray &r) {
  f64 t = HitSphere(point3(0.0, 0.0, -1.0), 0.5, r);
  if (t > 0.0) {
    vec3 N = glm::normalize(r.at(t) - vec3(0, 0, -1));
    return 0.5 * color(N.x + 1.0, N.y + 1.0, N.z + 1.0);
  }

  vec3 unit_dir = glm::normalize(r.direction());
  f64 a = 0.5 * (unit_dir.y + 1.0);
  return (1.0 - a) * color(1.0) + a * color(0.10, 0.150, 1.0);
}

int main(int argc, char *argv[]) {
  // image size
  f64 aspect_ratio{16.0 / 9.0};
  i32 image_width{800};
  i32 image_height{static_cast<i32>(image_width / aspect_ratio)};
  image_height = (image_height < 1) ? 1 : image_height;

  // camera
  f64 focal_length{1.0};
  f64 viewport_height{2.0};
  f64 viewport_width{viewport_height * (static_cast<f64>(image_width) /
                                        static_cast<f64>(image_height))};
  point3 camera_center(0.0);

  vec3 viewport_u(viewport_width, 0.0, 0.0);
  vec3 viewport_v(0.0, -viewport_height, 0.0);

  vec3 pixel_delta_u = viewport_u / static_cast<f64>(image_width);
  vec3 pixel_delta_v = viewport_v / static_cast<f64>(image_height);

  vec3 viewport_upper_left = camera_center - vec3(0.0, 0.0, focal_length) -
                             (viewport_u / 2.0) - (viewport_v / 2.0);
  vec3 pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (u32 h = 0; h < image_height; h++) {
    std::clog << "\rScanlines remaining: " << (image_height - h) << ' '
              << std::flush;
    for (u32 w = 0; w < image_width; w++) {
      point3 pixel_center(pixel00_loc + (f64(w) * pixel_delta_u) +
                          (f64(h) * pixel_delta_v));
      vec3 ray_direction(pixel_center - camera_center);
      Ray r(camera_center, ray_direction);

      color color(RayColor(r));
      std::cout << color;
    }
  }

  std::clog << "\rDone.                 \n";
  return 0;
}
