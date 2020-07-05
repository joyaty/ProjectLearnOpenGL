cmake_minimum_required(VERSION 3.10)

project(glad)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(ALL_FILES
src/glad.c
)

add_library(${PROJECT_NAME} ${ALL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "external")