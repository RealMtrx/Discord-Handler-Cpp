cmake_minimum_required(VERSION 3.16)
project(Discord-Handler-Cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    dpp
    GIT_REPOSITORY https://github.com/brainboxdotcc/DPP
    GIT_TAG v10.1.4
)

FetchContent_MakeAvailable(dpp)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE crypt32 ws2_32)
endif()
