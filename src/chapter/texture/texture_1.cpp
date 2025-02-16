//
// Created by 岳郅宇 on 2024/7/25.
//
#include <glad/glad.h>
#include <iostream>
#include "header/texture_1.h"
#include "../src/texture/header/stb_image.h"
#include "../src/shader/shader.h"
#include "../src/window/window.h"

void TextureChapterModule::deletegateMain(GLFWwindow* window)
{
    // 创建Shader
    auto* ourShader = new Shader("../assets/glsl/vertex_shader.vs", "../assets/glsl/fragment_shader.fs");

    /// 声明定点：
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
        -0.4f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下

        0.4f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 右下
        -0.5f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
    };

    // 声明定点信息
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // 顶点数据对象
    glGenBuffers(1, &VBO); // 顶点缓冲对象
    glGenBuffers(1, &EBO); // 顶点缓冲对象
    /// 绑定顶点数组
    glBindVertexArray(VAO);
    // 将数据导入缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int indices[] = {
        0, 1, 2, // first triangle
        3, 4, 5 // second triangle
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /// 获取纹理
    generateTexture();

    // 创建渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader->use();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /// 检查并调用事件、交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    delete ourShader;
}

//// 加载纹理
void TextureChapterModule::generateTexture()
{
    /// 加载图片
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../assets/resource/sample.jpeg", &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }
    unsigned int texture;
    glGenTextures(1, &texture); // N表示生成的纹理的数量，然后存储在第二个参数中（texture的指针）
    // 然后绑定它：
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // 使用图片生成纹理
    /// GL_TEXTURE_2D:w纹理目标，设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理。（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
    /// 多级渐变纹理的级别；
    /// 纹理加载为何种格式
    /// 宽度、高度
    /// 固定的0
    /// 原图格式和数据类型
    /// 图形数据
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 生成纹理之后，释放内存
    stbi_image_free(data);
}
