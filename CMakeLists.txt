cmake_minimum_required (VERSION 3.8)
project (computer_graphics)

set (CMAKE_CXX_STANDARD 17)
find_package (OpenGL REQUIRED)

add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy (SET CMP0026 OLD)
list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include (CreateLaunchers)
include (MSVCMultipleProcessCompile) # /MP

if (INCLUDE_DISTRIB)
    add_subdirectory (distrib)
endif (INCLUDE_DISTRIB)

include_directories (
    external/AntTweakBar-1.16/include/
    external/glfw-3.1.2/include/GLFW/
    external/glm-0.9.7.1/
    external/glew-1.13.0/include/
    external/assimp-3.0.1270/include/
    external/bullet-2.81-rev2613/src/
    .
)

set (ALL_LIBS
    ${OPENGL_LIBRARY}
    glut32
    glfw
    GLEW_1130
)

add_definitions (
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

set (CONTROLS_AND_SHADER
    common/controls.cpp
    common/controls.hpp
    common/shader.cpp
    common/shader.hpp
    ColorFragmentShader.fragmentshader
    TransformVertexShader.vertexshader
)

set (BASE_OPENGL
    main.hpp
    opengl.hpp
    opengl.cpp
)

file (GLOB_RECURSE OPENGL_OBJECTS "customs/*")

# Test
add_executable (Test check_version.cpp)
target_link_libraries (Test ${ALL_LIBS})

# Tugas 1 (Shape)
add_executable (circle circle.cpp)
target_link_libraries (circle ${ALL_LIBS})

# Tugas 2 (Rumah)
add_executable (rumah rumah.cpp)
target_link_libraries (rumah ${ALL_LIBS})

# Tugas 3 (3D Object)
add_executable (DDD DDD.cpp ${CONTROLS_AND_SHADER})
target_link_libraries (DDD ${ALL_LIBS})

# Tugas 4 (Rollercoaster)
add_executable (rollercoaster
    rollercoaster.cpp
    ${OPENGL_OBJECTS}
    ${CONTROLS_AND_SHADER}
)
target_link_libraries (rollercoaster ${ALL_LIBS})
