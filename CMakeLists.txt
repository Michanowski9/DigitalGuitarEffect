cmake_minimum_required(VERSION 3.15)

project(app)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

IF(NOT WIN32)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
ENDIF()

include_directories("${CMAKE_SOURCE_DIR}/lib/portaudio/include")

add_subdirectory(src)
add_subdirectory(test)
