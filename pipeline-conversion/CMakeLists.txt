cmake_minimum_required(VERSION 3.20)

project(pipeline-conversion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build tests" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)


include(FetchContent)

FetchContent_Declare(
        epanet
        GIT_REPOSITORY https://github.com/OpenWaterAnalytics/EPANET.git
        GIT_TAG        v2.3.5
)

# Prevent EPANET CLI tools from being built
set(EPANET_BUILD_EXECUTABLE OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(epanet)




file(GLOB VENDOR_DLLS_DEBUG
        "${PROJECT_SOURCE_DIR}/libs/debug/*.dll"
        "${PROJECT_SOURCE_DIR}/libs/debug/*.pdb"
)

file(GLOB VENDOR_DLLS_RELEASE
        "${PROJECT_SOURCE_DIR}/libs/release/*.dll"
)




add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
  include(CTest)
  enable_testing()

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_subdirectory(tests)
endif()
