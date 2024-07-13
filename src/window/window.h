//
// Created by 岳郅宇 on 2024/7/13.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <GLFW/glfw3.h>
/// 尺寸变更的回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// 处理输入的函数
void processInput(GLFWwindow* window);

#endif //WINDOW_H
