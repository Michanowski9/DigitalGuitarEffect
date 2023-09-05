file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_library(${CMAKE_PROJECT_NAME}_lib SHARED ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC ${CMAKE_SOURCE_DIR}/lib/portaudio/portaudio.lib)
