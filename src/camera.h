#pragma once
#include "glm/geometric.hpp"
#include "hittable.h"
#include "material.h"
#include "util/types.hpp"
#include "util/util.hpp"
#include <cmath>
#include <color.h>

class Camera {
public:
  f64 aspect_ratio{1.0};
  i32 image_width{100};
  i32 samples_per_pixel{10};
  i32 max_depth{10};

  f64 vfov{90};
  point3 lookfrom = point3(0);
  point3 lookat = point3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

private:
  i32 image_height;
  f64 pixel_samples_scale;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 u, v, w;

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
        color pixel_color(0, 0, 0);
        for (u32 sample = 0; sample < samples_per_pixel; sample++) {
          Ray r = GetRay(w, h);
          pixel_color += RayColor(r, max_depth, world);
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
    center = lookfrom;

    // viewport dimensions
    f64 focal_length{glm::length(lookfrom - lookat)};
    f64 theta{DegreeToRadians(vfov)};
    f64 h{std::tan(theta / 2.0)};
    f64 viewport_height{2.0 * h * focal_length};
    f64 viewport_width{viewport_height * (static_cast<f64>(image_width) /
                                          static_cast<f64>(image_height))};

    w = normalize(lookfrom - lookat);
    u = normalize(glm::cross(vup, w));
    v = glm::cross(w, u);

    vec3 viewport_u(viewport_width * u);
    vec3 viewport_v(viewport_height * -v);

    pixel_delta_u = viewport_u / static_cast<f64>(image_width);
    pixel_delta_v = viewport_v / static_cast<f64>(image_height);

    vec3 viewport_upper_left = center -(focal_length * w) -
                               (viewport_u / 2.0) - (viewport_v / 2.0);
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  Ray GetRay(i32 i, i32 j) const {
    vec3 offset = SampleSquare();
    point3 pixel_sample = pixel00_loc + ((i + offset.x) * pixel_delta_u) +
                          ((j + offset.y) * pixel_delta_v);

    point3 ray_origin = center;
    vec3 ray_direction = pixel_sample - ray_origin;
    return Ray(ray_origin, ray_direction);
  }
  vec3 SampleSquare() const {
    return vec3(Randomf64() - 0.5, Randomf64() - 0.5, 0);
  }

  color RayColor(const Ray &r, i32 depth, const Hittable &world) const {
    if (depth <= 0) {
      return color(0);
    }
    HitRecord rec;
    if (world.Hit(r, Interval(0.001, infinity), rec)) {
      Ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered))
        return attenuation * RayColor(scattered, depth - 1, world);
      return color(0);
    }

    vec3 unit_dir = glm::normalize(r.direction());
    f64 a = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - a) * color(1.0) + a * color(0.5, 0.7, 1.0);
  }
};
