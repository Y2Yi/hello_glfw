cmake_minimum_required(VERSION 3.28)
project(hello_glfw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++ -framework OpenGL -framework AppKit -framework IOKit -framework CoreGraphics")

file(GLOB_RECURSE SOURCE_CODE_LIB "src/*.cpp")
file(GLOB_RECURSE HEADER_LIB "src/*.h")
add_executable(hello_glfw
        ${CMAKE_SOURCE_DIR}/src/glad.c
        main.cpp
        ${SOURCE_CODE_LIB}
        ${HEADER_LIB}
)

include_directories(${CMAKE_SOURCE_DIR}/include)


link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(hello_glfw ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)