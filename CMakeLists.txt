cmake_minimum_required(VERSION 3.10)

PROJECT("GEOMETRY_2D")

find_package(OpenGL REQUIRED)

aux_source_directory(src MAIN_SRC)
aux_source_directory(geometry_draw DRAW_SRC)
aux_source_directory(geometry_2d GEOMETRY_SRC)
add_subdirectory(glfw)

set(EXECUTABLE_NAME geometry)
set(GEOMETRY_2D_LIB geometry_lib)
set(GEOMETRY_DRAW_LIB geometry_draw_lib)

add_executable(${EXECUTABLE_NAME} ${MAIN_SRC})

add_library(${GEOMETRY_DRAW_LIB} SHARED ${DRAW_SRC})
add_library(${GEOMETRY_2D_LIB} SHARED ${GEOMETRY_SRC})
target_link_libraries(${GEOMETRY_2D_LIB} ${GEOMETRY_DRAW_LIB})

include_directories(glm geometry_2d glfw/include include geometry_draw)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
        glfw GL ${GEOMETRY_2D_LIB})

add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/_shaders/ $<TARGET_FILE_DIR:geometry>/shaders)