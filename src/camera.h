#pragma once
#include "hittable.h"
#include "types.hpp"
#include "util.hpp"
#include <color.h>


class Camera {
public:
  f64 aspect_ratio     {1.0};
  i32 image_width      {100};
  i32 samples_per_pixel{10};
  i32 max_depth        {10};

private:
  i32 image_height;
  f64 pixel_samples_scale;
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
        color pixel_color(0,0,0);
        for(u32 sample = 0; sample< samples_per_pixel; sample++){
          Ray r = GetRay(w, h);
          pixel_color += RayColor(r,max_depth, world);
        }
        std::cout << pixel_samples_scale * pixel_color;
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  void Init() {
    image_height = i32(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    pixel_samples_scale = 1.0 / samples_per_pixel;
    center = point3(0,0,1.0);

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

  Ray GetRay(i32 i, i32 j) const {
    vec3 offset = SampleSquare();
    point3 pixel_sample = pixel00_loc 
      + ((i + offset.x) * pixel_delta_u)
      + ((j + offset.y) * pixel_delta_v);

    point3 ray_origin = center;
    vec3 ray_direction = pixel_sample - ray_origin;
    return Ray(ray_origin, ray_direction);
  }
  vec3 SampleSquare() const {
    return vec3(Randomf64() - 0.5, Randomf64() - 0.5, 0);
  }

  color RayColor(const Ray &r,i32 depth, const Hittable &world) const {
    if (depth <= 0) {
      return color(0);
    }
    HitRecord rec;
    if (world.Hit(r, Interval(0.001, infinity), rec)) {
      vec3 direction = rec.normal + RandomUnitv3();
      return 0.5 * RayColor(Ray(rec.p, direction),depth-1, world);
    }

    vec3 unit_dir = glm::normalize(r.direction());
    f64 a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * color(1.0) + a * color(0.5, 0.7, 1.0);
  }



};
