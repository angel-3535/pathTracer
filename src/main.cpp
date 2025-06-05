#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "util/types.hpp"
#include <memory>
#include <util/util.hpp>


int main(int argc, char *argv[]) {
  //World
  HittableList world;
  auto material_ground =  std::make_shared<Lambertian>(color(0.8,0.8,0));



  auto mate_red =         std::make_shared<Lambertian>(color(1.0,0.0,0.0));
  auto mate_green =       std::make_shared<Lambertian>(color(0.0,1.0,0.0));
  auto mate_blue =        std::make_shared<Lambertian>(color(0.0,0.0,1.0));
  auto metal_gray =       std::make_shared<Metal>(color(0.8,0.8,0.8));
  auto metal_white =      std::make_shared<Metal>(color(1));
  auto metal_red =        std::make_shared<Metal>(color(1.0,0.1,0.1));
  auto metal_green =      std::make_shared<Metal>(color(0.1,1.0,0.1));
  auto metal_blue =       std::make_shared<Metal>(color(0.1,0.1,1.0));
  auto glass =            std::make_shared<Dielectric>(1.75);

  world.add(std::make_shared<Sphere>(point3(0,0,-1.2)     ,0.5, glass));
  world.add(std::make_shared<Sphere>(point3(1.2,0,0)      ,0.5, mate_blue));

  world.add(std::make_shared<Sphere>(point3(0,  -.4,-2.2)  ,0.1, mate_red));
  world.add(std::make_shared<Sphere>(point3(0.3,-.4,-2.2)  ,0.1, mate_green));
  world.add(std::make_shared<Sphere>(point3(-.3,-.4,-2.2)  ,0.1, mate_blue));

  world.add(std::make_shared<Sphere>(point3(-1,0,-2)    ,0.5, metal_red));
  world.add(std::make_shared<Sphere>(point3(-2.2,0,0)   ,0.5, metal_green));
  world.add(std::make_shared<Sphere>(point3(1,1.5,-1)   ,0.7, metal_gray));
  world.add(std::make_shared<Sphere>(point3(1,0,-1)     ,0.5, metal_white));

  world.add(std::make_shared<Sphere>(point3(0,-100.5,-1),100, material_ground));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1280;
  cam.samples_per_pixel = 100;
  cam.max_depth = 100;


  cam.vfov = 65;
  cam.lookfrom = point3(-3,2,1);
  cam.lookat   = point3(0, 0, -1);


  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;


  cam.render(world);
  return 0;
}
