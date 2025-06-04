#pragma once

#include "util/util.hpp"
#include "util/v3util.hpp"
#include <cmath>
#include <hittable.h>

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r_in, const HitRecord &rec,
                       color &attenuation, Ray &scattered) const {
    return false;
  }
};

class Lambertian : public Material {
private:
  color albedo;

public:
  Lambertian(const color &albedo) : albedo(albedo) {}

  bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation,
               Ray &scattered) const override {

    vec3 scatter_direction = rec.normal + RandomUnitv3();

    if (Isv3NearZero(scatter_direction))
      scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

private:
};

class Metal : public Material {
private:
  color albedo;

public:
  Metal(const color &albedo) : albedo(albedo) {}

  bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation,
               Ray &scattered) const override {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  }
};

class Dielectric : public Material {
private:
  f64 refraction_index;

public:
  Dielectric(f64 refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation,Ray &scattered) const override {
    attenuation = color(1.0);
    f64 ri{rec.front_face ? (1.0 / refraction_index) : refraction_index};


    vec3 unit_direction{normalize(r_in.direction())};
    vec3 refracted{refract(unit_direction, rec.normal, ri)};

    f64 cos_theta = std::fmin(glm::dot(-unit_direction, rec.normal), 1.0);
    f64 sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
    bool can_refract{!(ri * sin_theta > 1.0)};
    vec3 direction;

    if(!can_refract || reflectance(cos_theta, ri) > Randomf64()){
      direction = reflect(unit_direction, rec.normal);
    }else{
      direction = refract(unit_direction, rec.normal,ri);
    }
    scattered = Ray(rec.p, direction);

    return true;
  }

private:

  static f64 reflectance(f64 cosine, f64 refraction_index){
    f64 r0 = (1 - refraction_index)  / (1 + refraction_index);
    r0 = r0* r0;
    return r0 + (1-r0) * std::pow((1 - cosine), 5);
  }
};
