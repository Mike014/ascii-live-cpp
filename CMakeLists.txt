cmake_minimum_required(VERSION 3.14)
project(ascii-live-Cpp LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG        v0.18.3
)

FetchContent_MakeAvailable(httplib)

add_executable(ascii-live-cpp main.cpp)

target_include_directories(ascii-live-cpp PRIVATE frames)

target_compile_definitions(ascii-live-cpp PRIVATE CPPHTTPLIB_NO_COMPRESS)

target_link_libraries(ascii-live-cpp PRIVATE httplib)

if (WIN32)
    target_link_libraries(ascii-live-cpp PRIVATE ws2_32)
endif()

if (MINGW)
    target_link_options(ascii-live-cpp PRIVATE -static)
endif()

