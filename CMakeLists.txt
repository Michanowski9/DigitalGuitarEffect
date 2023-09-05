cmake_minimum_required(VERSION 3.15)

project(app)

IF(WIN32)
    set(CMAKE_GENERATOR "Visual Studio 17 2022 Win64")
    message("Generator is set to ${CMAKE_GENERATOR}")
ENDIF()

include_directories("${CMAKE_SOURCE_DIR}/lib/portaudio/include")

add_subdirectory(src)

