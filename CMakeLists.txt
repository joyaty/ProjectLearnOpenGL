# the required of cmake version
cmake_minimum_required(VERSION 3.10)

# project name
project(ProjectLearnOpenGL)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Prevent creates default "CMakePredefinedTargets" folder
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "")

# set cpp standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/glad)
add_subdirectory(src/0.test_case)