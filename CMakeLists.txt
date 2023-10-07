cmake_minimum_required(VERSION 3.15)

project(app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories("${CMAKE_SOURCE_DIR}/lib/portaudio/include")

add_subdirectory(src)
#add_subdirectory(test)
