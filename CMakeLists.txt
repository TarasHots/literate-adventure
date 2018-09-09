cmake_minimum_required(VERSION 3.10)
project(SFML_fun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.4 REQUIRED COMPONENTS network audio graphics window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

add_executable(SFML_fun main.cpp)
target_link_libraries(SFML_fun ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

