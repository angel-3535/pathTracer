#pragma once

#include "hittable.h"
#include "interval.h"
#include <util/util.hpp>
#include <vector>

class HittableList : public Hittable {
public:
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object) { add(object); }
  void clear() { objects.clear(); }
  void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

  bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override {
    HitRecord temp_rec{};
    bool hit_anything{false};
    f64 closest_so_far{ray_t.max};

    for (const auto &object : objects) {
      if (object->Hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }
    return hit_anything;
  }

};
