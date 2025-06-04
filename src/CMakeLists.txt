target_sources(${PROJECT_NAME}
  PRIVATE 
  FILE_SET util_headers
  TYPE HEADERS 
  FILES
    camera.h
    color.h
    hittable.h
    hittable_list.h
    interval.h
    material.h
    ray.h
    sphere.h
)
