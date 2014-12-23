cmake_minimum_required(VERSION 2.8.4)
project(shader_utils)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HEADERS shader_utils.h)
set(SOURCE_FILES main.cpp shader_utils.cpp)
add_executable(shader_utils ${SOURCE_FILES})

target_link_libraries(shader_utils  ${GLFW_LIBRARIES} X11 Xxf86vm Xrandr pthread Xi ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})

set(shaders "valid_vertex_shader.glsl"
            "valid_fragment_shader.glsl"
            "invalid_vertex_shader.glsl"
            "invalid_fragment_shader.glsl")

if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    foreach(item IN LISTS shaders)
        configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/${item}
            ${CMAKE_CURRENT_BINARY_DIR}/${item}
            COPYONLY
        )
    endforeach()
endif()
