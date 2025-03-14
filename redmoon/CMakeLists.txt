cmake_minimum_required(VERSION 3.26.0)
set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

project(redmoon VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} htap)