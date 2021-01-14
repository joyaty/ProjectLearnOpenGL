cmake_minimum_required(VERSION 3.10)

project("0.test_case")

message("PROJECT_NAME = " ${PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/../../external/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/../../external/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/../../external/glm.0.9.9.8/include)

link_directories(${PROJECT_SOURCE_DIR}/../../external/glfw/lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(ALL_FILES 
utils/Shader.cpp
utils/Shader.h
utils/stb_image.h
draw_triangle.cpp
test_texture.cpp
test_transformation.cpp
main.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "ProjectLearnOpenGL")

target_link_libraries(${PROJECT_NAME} glfw3 glad)