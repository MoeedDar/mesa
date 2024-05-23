cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER g++)

project(
    Mesa 
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES}) 

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_NAME ${PROJECT_NAME}
    LINKER_LANGUAGE CXX
)

find_library(FLECS flecs)
target_link_libraries(${PROJECT_NAME} ${FLECS})

find_library(RAYLIB raylib)
target_link_libraries(${PROJECT_NAME} ${RAYLIB})


SET(CMAKE_CXX_FLAGS_DEBUG "-g")
