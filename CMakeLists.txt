cmake_minimum_required(VERSION 3.26.0)
project(redmoon VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE vendor/asio-1.30.2/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -O2 # Or -O3 for more aggressive optimization, -Og for debug optimizations
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /O2 # Or /Ox, /Od
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
    endif()
endif()

#Optional: Install rules.
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY vendor DESTINATION include) # or wherever you need to install the vendor includes.
