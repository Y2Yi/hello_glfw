cmake_minimum_required(VERSION 3.28)
project(hello_glfw)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++ -framework OpenGL -framework AppKit -framework IOKit -framework CoreGraphics")

add_executable(hello_glfw ${CMAKE_SOURCE_DIR}/src/glad.c main.cpp
        src/shader/shader.h
        src/shader/shader.cpp
        src/window/window.cpp
        src/window/window.h
        src/gl_helper/GlHelper.cpp
        src/gl_helper/GlHelper.h
        src/texture/header/stb_image.h
        src/texture/stb_image.cpp
        src/chapter/texture/texture_1.cpp
        src/chapter/chapter_module/ChapterModule.cpp
        src/chapter/chapter_module/ChapterModule.h)

include_directories(${CMAKE_SOURCE_DIR}/include)


link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(hello_glfw ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)