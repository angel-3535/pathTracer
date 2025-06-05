#include "camera.h"
#include "glm/geometric.hpp"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "util/types.hpp"
#include "util/v3util.hpp"
#include <memory>
#include <util/util.hpp>

int main(int argc, char *argv[]) {
  // World
  HittableList world;
  auto material_ground = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, material_ground));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = Randomf64();
      point3 center(a + 0.9 * Randomf64(), 0.2, b + 0.9 * Randomf64());
      if (glm::length(center - point3(4, 0.2, 0)) > 0.9) {
        std::shared_ptr<Material> sphere_material;
        if ( choose_mat < 0.8) {
          auto albedo = RandomColor();
          sphere_material = std::make_shared<Lambertian>(albedo);
        } else if (choose_mat < 0.95) {
          auto albedo = RandomColor();
          auto fuzz = Randomf64(0.5, 1);
          sphere_material = std::make_shared<Metal>(albedo);
        } else {
          sphere_material = std::make_shared<Dielectric>(1.5);
        }
        world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
      }
    }
  }


  auto material1 = std::make_shared<Dielectric>(1.5);
  world.add(std::make_shared<Sphere>(point3(0,1,0),1.0,material1));

  auto material2 = std::make_shared<Lambertian>(color(0.4,0.2,0.1));
  world.add(std::make_shared<Sphere>(point3(-4,1,0),1.0,material2));

  auto material3 = std::make_shared<Metal>(color(0.7,0.6,0.5));
  world.add(std::make_shared<Sphere>(point3(4,1,0),1.0,material3));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1280;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.vfov = 20;
  cam.lookfrom = point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);

  cam.defocus_angle = 0.6;
  cam.focus_dist = 10.0;

  cam.render(world);
  return 0;
}
