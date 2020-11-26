aux_source_directory(. SRC_DIR)
include_directories(../include ../glm)

find_package(OpenGL REQUIRED)
add_executable(geometry_2d ${SRC_DIR})
if (WIN32)
    target_link_libraries(geometry_2d glfw opengl32)
else()
    target_link_libraries(geometry_2d glfw GL)
endif()

add_custom_command(TARGET geometry_2d PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/_shaders/ $<TARGET_FILE_DIR:geometry_2d>/shaders)
