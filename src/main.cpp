#include "camera.h"
#include "glm/detail/type_vec3.hpp"
#include "glm/geometric.hpp"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "sphere.h"
#include "types.hpp"
#include <memory>
#include <util/util.hpp>


int main(int argc, char *argv[]) {
  //World
  HittableList world;
  world.add(std::make_shared<Sphere>(point3(0,0,-1),0.5));
  world.add(std::make_shared<Sphere>(point3(0,-100.5,-1),100));

  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 800;

  cam.render(world);
  return 0;
}
