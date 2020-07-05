cmake_minimum_required(VERSION 3.10)

project("0.test_case")

message("PROJECT_NAME = " ${PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/../../external/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/../../external/glad/include)

link_directories(${PROJECT_SOURCE_DIR}/../../external/glfw/lib)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "ProjectLearnOpenGL")

target_link_libraries(${PROJECT_NAME} glfw3 glad)