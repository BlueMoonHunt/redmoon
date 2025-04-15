cmake_minimum_required(VERSION 3.26.0)
project(redmoon VERSION 0.1.0 LANGUAGES C CXX)

# Output directories for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Require C++23
target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_std_23
)

# Set compiler warnings
target_compile_options(${PROJECT_NAME}
    PRIVATE
    "-Wall"
    "-Wpedantic"
)

# --- Dependencies ---
include(FetchContent)

# Base SDL3 library
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    message(STATUS "SDL3 not found, fetching via FetchContent...")
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main # Consider using a specific release tag for stability
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/SDL3
        GIT_SHALLOW TRUE
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_MakeAvailable(SDL3)
else()
    message(STATUS "Found system SDL3")
endif()

add_subdirectory(vendor/SDL3_ttf)
add_subdirectory(vendor/SDL3_image)
add_subdirectory(vendor/SDL3_mixer)
add_subdirectory(vendor/glm)

# --- Linking Dependencies ---
# Link against the imported targets provided by SDL3 and its extensions (modern CMake)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
    glm::glm
)

# --- Include Directories ---
# FetchContent usually handles this, but add src for local includes.
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    vendor/SDL3_ttf/include
    vendor/SDL3_mixer/include
    vendor/SDL3_image/include
)

# --- Resource File Handling ---
# Copy resource files to the build output directory
set(RESOURCE_SRC_DIR "${CMAKE_SOURCE_DIR}/res")
set(RESOURCE_DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RESOURCE_SRC_DIR}"
    "${RESOURCE_DEST_DIR}"
    COMMENT "Copying resource files to ${RESOURCE_DEST_DIR}"
    VERBATIM
)

# Ensure resources are copied before the executable is potentially run/installed
add_dependencies(${PROJECT_NAME} copy_resources)

# --- Build Messages ---
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Output Executable: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}")
message(STATUS "Resource Destination (Build): ${RESOURCE_DEST_DIR}")
