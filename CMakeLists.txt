cmake_minimum_required(VERSION 4.0)
project(pathTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

add_subdirectory( dep/glm )

#==========================================

list(APPEND SRC_FILES 
  "src/main.cpp"
)

add_executable( ${PROJECT_NAME} ${SRC_FILES} )

add_subdirectory( src/util )

target_link_libraries(${PROJECT_NAME}  glm::glm)

#==========================================

#INCLUDE DIRECTORIES
include_directories( ${OPENGL_INCLUDE_DIRS} )
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/dep/glm")

target_include_directories( ${PROJECT_NAME} PRIVATE ${EXTRA_INCLUDES})

#COMPILE DEF
add_compile_definitions(GL_VERSION_MAJOR=4)
add_compile_definitions(GL_VERSION_MINOR=1)
#==========================================

