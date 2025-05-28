#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include <util/util.hpp>


int main(int argc, char *argv[]) {
  //World
  HittableList world;
  world.add(std::make_shared<Sphere>(point3(0,0,-1),0.5));
  world.add(std::make_shared<Sphere>(point3(3,2,-3),0.5));
  world.add(std::make_shared<Sphere>(point3(-3,1,-3),0.7));
  world.add(std::make_shared<Sphere>(point3(0,-100.5,-1),100));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1920;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
  return 0;
}
