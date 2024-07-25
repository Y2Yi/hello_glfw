#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/window/window.h"
#include "src/shader/shader.h"
#include "src/chapter/texture/header/texture_1.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /// 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /// 告诉OpenGL Viewport的尺寸、注册尺寸变更的回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto* chapterModule = new TextureChapterModule();

    chapterModule->deletegateMain(window);

    delete chapterModule;

    /// 确保GLFW资源能够被正确地释放
    glfwTerminate();

    return 0;
}
