find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_custom_target(
    run_app ALL
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/src/python/main.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_dependencies(run_app ${CMAKE_PROJECT_NAME}_lib)

