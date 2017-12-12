cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
project (computer_graphics)

find_package (OpenGL REQUIRED)
add_subdirectory (external)

if (INCLUDE_DISTRIB)
    add_subdirectory (distrib)
endif (INCLUDE_DISTRIB)

include_directories (
    external/AntTweakBar-1.16/include
    external/glfw-3.2.1/include/GLFW
    external/glm-0.9.8.5
    external/glew-1.13.0/include/GL
    external/glew-1.13.0/include
    external/assimp-3.0.1270/include
    external/bullet-2.81-rev2613/src
    ${CMAKE_SOURCE_DIR}
)

add_definitions (
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

file (GLOB_RECURSE COMMON "common/*")
file (GLOB_RECURSE CUSTOM "custom/*")
file (GLOB_RECURSE SHADER "shader/*")
set (GL_LIBS ${OPENGL_LIBRARY} glut32 glfw GLEW_1130)
set (GRAFKOM ${SHADER} ${COMMON} ${CUSTOM})

# Test
add_executable (check_version check_version.cpp)
target_link_libraries (check_version ${GL_LIBS})

# Tugas 1 (Shape)
add_executable (circle circle.cpp)
target_link_libraries (circle ${GL_LIBS})

# Tugas 2 (Rumah)
add_executable (rumah rumah.cpp)
target_link_libraries (rumah ${GL_LIBS})

# Tugas 3 (3D Object)
add_executable (DDD DDD.cpp ${GRAFKOM})
target_link_libraries (DDD ${GL_LIBS})

# Tugas 4 (Rollercoaster)
add_executable (rollercoaster rollercoaster.cpp ${GRAFKOM})
target_link_libraries (rollercoaster ${GL_LIBS})

# Tugas 5 (KubusMutar)
add_executable (kubusmutar kubusmutar.cpp ${GRAFKOM})
target_link_libraries (kubusmutar ${GL_LIBS})
