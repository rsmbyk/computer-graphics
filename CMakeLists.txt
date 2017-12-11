cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
project (computer_graphics)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy (SET CMP0026 OLD)
list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include (CreateLaunchers)
include (MSVCMultipleProcessCompile) # /MP

find_package (OpenGL REQUIRED)
add_subdirectory (external)

if (INCLUDE_DISTRIB)
    add_subdirectory (distrib)
endif (INCLUDE_DISTRIB)

#include_directories (
#    external/AntTweakBar-1.16/include/
#    external/glfw-3.1.2/include/GLFW/
#    external/glm-0.9.7.1/
#    external/glew-1.13.0/include/
#    external/assimp-3.0.1270/include/
#    external/bullet-2.81-rev2613/src/
#)

add_definitions (
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

set (GL_LIBS ${OPENGL_LIBRARY} glut32 glfw GLEW_1130)

file (GLOB_RECURSE CUSTOM "custom/*")
file (GLOB_RECURSE COMMON "common/*")
set (SHADER ColorFragmentShader.fragmentshader TransformVertexShader.vertexshader)
set (GRAFKOM ${SHADER} ${COMMON} ${CUSTOM})

# Test
add_executable (test check_version.cpp)
target_link_libraries (test ${GL_LIBS})

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
