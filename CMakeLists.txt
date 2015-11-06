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
set(LIB_FILES shader_utils.cpp)
set(SOURCE_FILES main.cpp ${LIB_FILES})
#add_executable(shader_utils ${SOURCE_FILES})

#target_link_libraries(shader_utils  ${GLFW_LIBRARIES} X11 Xxf86vm Xrandr pthread Xi ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

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

# build static library
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
add_library(shaderutils STATIC ${HEADERS} ${LIB_FILES})
target_include_directories(shaderutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(shaderutils  ${GLEW_LIBRARIES})
