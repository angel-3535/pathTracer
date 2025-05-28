#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "types.hpp"
#include <memory>
#include <util/util.hpp>


int main(int argc, char *argv[]) {
  //World
  HittableList world;
  auto material_ground = std::make_shared<Lambertian>(color(0.8,0.8,0));
  auto material_center = std::make_shared<Lambertian>(color(0.1,0.2,0.5));
  auto material_left = std::make_shared<Metal>(color(0.8,0.8,0.8));
  auto material_right = std::make_shared<Metal>(color(0.8,0.6,0.2));

  world.add(std::make_shared<Sphere>(point3(0,0,-1.2),0.5, material_center));
  world.add(std::make_shared<Sphere>(point3(1,0,-1),0.5, material_right));
  world.add(std::make_shared<Sphere>(point3(-1,0,-1),0.5, material_left));
  world.add(std::make_shared<Sphere>(point3(3,2,-3),0.5, material_center));
  world.add(std::make_shared<Sphere>(point3(-3,1,-3),0.7, material_center));
  world.add(std::make_shared<Sphere>(point3(0,-100.5,-1),100, material_ground));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1920;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
  return 0;
}
