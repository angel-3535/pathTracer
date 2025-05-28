#pragma once
#include "hittable.h"
#include <util.h>

class Camera {
public:
  f64 aspect_ratio{1.0};
  i32 image_width{100};

private:
  i32 image_height;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

public:
  Camera() = default;
  ~Camera() = default;

  void render(const Hittable &world) {
    Init();
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (u32 h = 0; h < image_height; h++) {
      std::clog << "\rScanlines remaining: " << (image_height - h) << ' '
                << std::flush;
      for (u32 w = 0; w < image_width; w++) {
        point3 pixel_center(pixel00_loc + (f64(w) * pixel_delta_u) +
                            (f64(h) * pixel_delta_v));
        vec3 ray_direction(pixel_center - center);
        Ray r(center, ray_direction);

        color pixel_color(RayColor(r, world));
        std::cout << pixel_color;
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  void Init() {
    image_height = i32(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    center = point3(0);

    // viewport dimensions
    f64 focal_length{1.0};
    f64 viewport_height{2.0};
    f64 viewport_width{viewport_height * (static_cast<f64>(image_width) /
                                          static_cast<f64>(image_height))};

    vec3 viewport_u(viewport_width, 0.0, 0.0);
    vec3 viewport_v(0.0, -viewport_height, 0.0);

    pixel_delta_u = viewport_u / static_cast<f64>(image_width);
    pixel_delta_v = viewport_v / static_cast<f64>(image_height);

    vec3 viewport_upper_left = center - vec3(0.0, 0.0, focal_length) -
                               (viewport_u / 2.0) - (viewport_v / 2.0);
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  color RayColor(const Ray &r, const Hittable &world) const {
    HitRecord rec;
    if (world.Hit(r, Interval(0, infinity), rec)) {
      return 0.5 * (rec.normal + color(1));
    }

    vec3 unit_dir = glm::normalize(r.direction());
    f64 a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * color(1.0) + a * color(0.5, 0.7, 1.0);
  }
};
