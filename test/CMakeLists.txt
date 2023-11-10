cmake_minimum_required(VERSION 3.15)

include(FetchContent)
FetchContent_Declare(
	googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${CMAKE_SOURCE_DIR}/googletest/include"
                    "${CMAKE_SOURCE_DIR}/googlemock/include")
include_directories("${CMAKE_SOURCE_DIR}/src/native")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
set(SOURCES ${TEST_SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_test PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)

add_custom_target(
    run_tests ALL
    COMMAND ${CMAKE_SOURCE_DIR}/bin/Release/${CMAKE_PROJECT_NAME}_test.exe 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_dependencies(run_tests ${CMAKE_PROJECT_NAME}_test)

