#pragma once

#include "util.hpp"
#include <hittable.h>

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r_in, const HitRecord &rec,
                       color &attenuation, Ray &scattered) const {
    return false;
  }
};


class Lambertian : public Material{
private:
    color albedo;
public:
  Lambertian(const color& albedo) : albedo(albedo){}

 bool scatter(const Ray &r_in, const HitRecord &rec,
                       color &attenuation, Ray &scattered) const override {
   vec3 scatter_direction = rec.normal + RandomUnitv3();

   if(Isv3NearZero(scatter_direction))
     scatter_direction = rec.normal;

   scattered = Ray(rec.p, scatter_direction);
   attenuation = albedo;
   return true;
 }

private:
};


class Metal : public Material{
private:
    color albedo;
public:
  Metal(const color& albedo) : albedo(albedo){}

 bool scatter(const Ray &r_in, const HitRecord &rec,
                       color &attenuation, Ray &scattered) const override {
   vec3 reflected = reflect(r_in.direction(), rec.normal);
   scattered = Ray(rec.p, reflected);
   attenuation = albedo;
   return true;
 }

private:
};


