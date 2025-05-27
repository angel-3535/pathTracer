#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <string>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

using vec4 = glm::dvec4;
using fvec4 = glm::vec4;
using ivec4 = glm::ivec4;

using vec3 = glm::dvec3;
using fvec3 = glm::vec3;
using ivec3 = glm::ivec3;

using point3 = glm::dvec3;
using fpoint3 = glm::vec3;
using ipoint3 = glm::ivec3;

using vec2 = glm::dvec2;
using fvec2 = glm::vec2;
using ivec2 = glm::ivec2;

using color =  glm::dvec3;
using fcolor =  glm::fvec3;
using icolor =  glm::ivec3;

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;

using String = std::string;

