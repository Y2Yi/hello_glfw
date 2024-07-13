#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./src/window/window.h"
#include "./src/gl_helper/GlHelper.h"
#include "src/shader/shader.h"

class Shader;

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

    // 创建Shader
    Shader* ourShader = new Shader("./glsl/vertex_shader.vs", "./glsl/fragment_shader.fs");

    /// 声明定点：
    float vertices[] = {
        // positions         // colors
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };
    // 声明定点信息
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // 顶点数据对象
    glGenBuffers(1, &VBO); // 顶点缓冲对象
    // bind the Vertex Array Object first
    glBindVertexArray(VAO); // 绑定当前程序的顶点数组对象

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定当前程序的顶点缓冲对象

    // 将数据导入缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置数据
    // 0:和location对应；
    // 3:个分量
    // float: 类型
    // false: 不进行标准化
    // 不同组间相同分量的步长（xyzrgb，xyzrgb中x到x的距离）
    // 0: 组间偏移量（位置xyz是0，而rgb显然是3 x sizeof(float)）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 创建渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        int uniform_vertexOffset = glGetUniformLocation(ourShader->ID, "offset_uniform"); // 找到Uniform
        // 绑定Uniform
        /// 注意，这个步骤必须发生在use之后
        glUniform3f(uniform_vertexOffset, 0.5f, 0.5, 0);
        ourShader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /// 检查并调用事件、交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    /// 确保GLFW资源能够被正确地释放
    glfwTerminate();
    delete ourShader;

    return 0;
}
