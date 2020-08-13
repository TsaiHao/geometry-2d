aux_source_directory(. SRC_DIR)
include_directories(../include ../glm)

find_package(OpenGL REQUIRED)
add_executable(test ${SRC_DIR})
target_link_libraries(test glfw opengl32)
