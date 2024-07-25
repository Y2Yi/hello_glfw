//
// Created by 岳郅宇 on 2024/7/25.
//
#pragma once

#include <GLFW/glfw3.h>

class ChapterModule
{
public:
    virtual ~ChapterModule() = default;
    ChapterModule() = default;
    virtual void deletegateMain(GLFWwindow* window) = 0;
};
